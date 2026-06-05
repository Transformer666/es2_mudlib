// 天師道法【紫雷咒】 taoism-thunder -- 天師派紫衣弟子的入門雷術
//
// 這是一門法術(magic)技能﹐天師派紫衣(雷)分支的根本道法。本檔比照
// 玄衣風咒 daemon (taoism-wind.c) 的結構建立﹐使技能可被指派與習練。
//
// === 具名咒 cast(2026-06-05 接通元素-效果引擎 + 九龍超載) ===
// docs/03-門派與武功/02-道士-天師與茅山.md「紫衣派(雷)— taoism-thunder」(L150)
// 雷法四式逐項對齊﹐以本檔既有三式承載 docs 效果(同火/冰範式﹐elem="thunder")：
//   docs 澤雷  swamp thunder    50%                 → 紫雷(入門雷罡)
//   docs 爆雷  blaster thunder  25% + 當前神 1/8     → 紫府裂空(附「神蓄」加成)
//   docs 神光雷 divine thunder  目標神傷 33%(無視抗性) → 紫電引雷(穿抗 + 削神)
// 雷術為「純雷元素傷害」一系﹐各式 elem="thunder"﹐傷害經
// /std/magic.c::magic_element_damage 折算對象雷抗(apply/thunder_def)。
//
// === 九龍超載 overload(docs L163 + daemon/skill/nine-dragon_force.c 旗標契約)===
// nine-dragon_force.c::do_overload 立下旗標 me->query_temp("force/taoism_overload")
//   (= 50)﹐表「下次天師咒基礎傷害 +50%」。本檔施咒命中後讀此旗標：基礎傷害
//   先 +該百分比﹐再 delete_temp 清旗標(僅及「下次」一道)。docs 六卦熒雷
//   「觸發但不消耗 overload」之旗標 → 本表以 "keep_overload":1 標記(該式吃加成
//   但不清旗標)﹔本入門三式無此旗標﹐均屬「吃加成並清旗標」之常態。

#include <ansi.h>

inherit "/std/magic";

mapping *actions = ({
  ([
    "action":		"$N口誦真言﹐指尖一道紫雷射向$n的$l",
    "dodge":		5,
    "damage":		5,
    "damage_type":	"雷傷"
  ]),
  ([
    "action":		"$N掐訣引雷﹐一道紫電轟向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"雷傷"
  ]),
  ([
    "action":		"$N袖中紫符鼓盪﹐化作一片雷網罩向$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"雷傷"
  ]),
  ([
    "action":		"$N凝神運法﹐一式『紫府裂空』激射$n的$l",
    "dodge":		-15,
    "damage":		10,
    "damage_type":	"雷傷"
  ]),
  ([
    "action":		"$N揮手撒出一蓬雷珠﹐密密麻麻地轟向$n的$l",
    "dodge":		-10,
    "damage":		5,
    "damage_type":	"雷傷"
  ]),
  ([
    "action":		"$N足踏罡步﹐一道雷龍盤旋著撲向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"雷傷"
  ]),
  ([
    "action":		"$N後退半步﹐凝起一團紫雷轟向$n的$l",
    "dodge":		10,
    "damage":		5,
    "damage_type":	"雷傷"
  ]),
  ([
    "action":		"$N雙掌一推﹐一式『紫電引雷』霹靂暴鳴﹐席捲$n的$l",
    "dodge":		0,
    "damage":		10,
    "damage_type":	"雷傷"
  ]),
});

string *interattack = ({
  "$N默運雷訣﹐指間隱隱透出一縷紫芒﹐靜待施法的時機。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("taoism-thunder");
  setup();
}

void
attack_using (object me, object opponent, object weapon)
{
  int damage;

  if (!opponent)
    {
      if (me->query_temp("last_attacked_target"))
	message_vision (HIC + interattack[random(sizeof(interattack))] + NOR, me, weapon);
      return;
    }

  damage = COMBAT_D->fight(me, opponent, "taoism-thunder", actions[random(sizeof(actions))], weapon);
}

// ── 主動施法(cast)：本門咒文表 + 技能名（valid_enable 由 /std/magic 提供；
//    cast_spell 於本檔 override 以接通元素引擎 + 九龍超載）──
string magic_skill() { return "taoism-thunder"; }

// 九龍超載旗標 key/值(鏡 daemon/skill/nine-dragon_force.c 之契約﹐毋直接 include
// 其檔﹔此處複述常數以對齊。do_overload set_temp(key, 50)﹐cast 端讀後 delete_temp)。
#define NDF_OVERLOAD_TEMP   "force/taoism_overload"

// 前置宣告(lesson #12)。
varargs int cast_spell(object me, string spl, object target);

// 雷法具名咒(docs L150「紫衣派(雷)— taoism-thunder」雷法四式)。各式 elem="thunder"﹐
// 傷害經 magic_element_damage 折算雷抗(apply/thunder_def)。效果旗標(供本檔 override 讀)：
//   "pierce":1        命中忽視雷抗(docs 神光雷「無視抗性」)。
//   "sen_charge":N    額外基礎傷 = 施法者當前神/N(docs 爆雷「+ 當前神 1/8」﹐N=8)。
//   "drain_sen":N     對目標削神(consume_stat "sen")= 本次傷害 N%(docs 神光雷「神傷 33%」)。
//   "delay":N         施法者施後 start_busy N(無則沿基底 2)。
mapping query_spells()
{
  return ([
    // 澤雷 swamp thunder：入門雷罡(docs 澤雷 50%)。
    "紫雷" :     ([ "id":"zilei",   "sen":8,  "power":12, "type":"雷殛",
        "elem":"thunder", "delay":1,
        "action":HIY "$N口誦真言﹐掐訣一引﹐一道紫雷脫手飛出﹐「霹」地轟向$n！" NOR ]),
    // 爆雷 blaster thunder：基礎較低﹐附「當前神 1/8」蓄能加成(docs 爆雷)。
    "紫府裂空" : ([ "id":"ziputie", "sen":16, "power":16, "type":"雷殛",
        "elem":"thunder", "delay":1, "sen_charge":8,
        "action":HIY "$N足踏罡步﹐袖中紫符鼓盪﹐一式『紫府裂空』盡引周身神識化作雷網紫電﹐激射$n！" NOR ]),
    // 神光雷 divine thunder：穿雷抗﹐並削目標神識(docs 神光雷 神傷 33%/無視抗性)。
    "紫電引雷" : ([ "id":"zidian",  "sen":30, "power":34, "type":"雷殛",
        "elem":"thunder", "delay":2, "pierce":1, "drain_sen":33,
        "action":HIY "$N凝神運法﹐周身雷光暴漲﹐一式『紫電引雷』神光霹靂沖天暴鳴﹐當頭劈向$n！" NOR ]),
  ]);
}

// ── override cast_spell：沿用 /std/magic 基底驗證流程﹐傷害改走元素引擎﹐
//    並接通九龍超載(下次基礎傷 +50%)與各式具名特效(蓄神/削神)。──
varargs int
cast_spell(object me, string spl, object target)
{
    mapping spells, sp;
    string sk, nm, action, dtype, elem;
    int cost, power, skill, base, damage, busy, overload;
    object fu;

    if( !objectp(me) || !stringp(spl) ) return 0;

    sk = magic_skill();
    spells = query_spells();
    if( !sk || !mapp(spells) || !sizeof(spells) ) {
        notify_fail("你還沒有可施展的法術。\n");
        return 0;
    }

    // 找咒文：先比中文名、再比英文 id。
    sp = spells[spl];
    if( !mapp(sp) ) foreach( nm, mapping m in spells )
        if( mapp(m) && m["id"] == spl ) { sp = m; break; }
    if( !mapp(sp) ) {
        notify_fail("你不會「" + spl + "」這道法術。\n");
        return 0;
    }

    // 須已習得本門法術。
    if( me->query_skill(sk) <= 0 && !me->query_learn(sk) ) {
        notify_fail("你並未習得「" + to_chinese(sk) + "」。\n");
        return 0;
    }

    // 取施法對象（cast 未指定時取當前敵人）。
    if( !objectp(target) ) {
        object *es = me->query_enemy();
        if( arrayp(es) ) {
            es -= ({ 0 });
            if( sizeof(es) ) target = es[0];
        }
    }
    if( !objectp(target) || !living(target)
    ||  target->query("life_form") == "ghost" ) {
        notify_fail("你要對誰施展法術？（cast " + spl + " on <對象>）\n");
        return 0;
    }
    if( target == me ) {
        notify_fail("你不能對自己施展攻擊法術。\n");
        return 0;
    }
    if( environment(me) != environment(target) ) {
        notify_fail("施法對象不在這裡。\n");
        return 0;
    }

    // 非戰之地不可施展攻擊法術。
    if( environment(me)->query("no_fight")
    && !target->query("unprotect_mark") && !me->query("unprotect_mark") ) {
        notify_fail("這裡是清靜之地，不可動手施法。\n");
        return 0;
    }

    // 神(sen)消耗檢查。
    cost = sp["sen"];
    if( me->query_stat("sen") < cost ) {
        notify_fail("你的神識不足以運使這道法術。\n");
        return 0;
    }

    // 符(talisman)消耗檢查(雷法未標 fu﹐此段略過；保留以與基底契約一致)。
    fu = 0;
    if( stringp(sp["fu"]) ) {
        fu = present(sp["fu"], me);
        if( !objectp(fu) || (int)fu->query_amount() < 1 ) {
            notify_fail("你身上沒有施展此法所需的"
                + (fu ? (string)fu->name() : (string)sp["fu"]) + "。\n");
            return 0;
        }
    }

    // ── 通過所有檢查，正式施法 ──
    if( !me->is_fighting(target) ) {
        me->kill_ob(target);
        if( userp(target) ) target->fight_ob(me);
        else target->kill_ob(me);
    }

    me->consume_stat("sen", cost);
    if( objectp(fu) )
        fu->add_amount(-1);

    // 基礎傷害(神/技能驅動﹐同基底公式)。
    skill = me->query_skill(sk);
    power = sp["power"];
    base = power * (100 + skill) / 100;

    // 爆雷蓄能：額外基礎傷 = 施法者當前神/N(docs 爆雷「+ 當前神 1/8」)。
    if( sp["sen_charge"] > 0 )
        base += me->query_stat("sen") / sp["sen_charge"];

    base += random(base / 2 + 1);

    // ── 九龍超載(docs L163)：旗標非 0 則基礎傷 +該百分比﹐用後清旗標 ──
    // (六卦熒雷類 "keep_overload":1 之式吃加成但不清﹔本入門三式無此旗標)。
    overload = (int)me->query_temp(NDF_OVERLOAD_TEMP);
    if( overload > 0 ) {
        base = base * (100 + overload) / 100;
        if( !sp["keep_overload"] )
            me->delete_temp(NDF_OVERLOAD_TEMP);
        tell_object(me, HIM "你周身蓄勢的雷龍轟然爆發﹐這一道天師咒雷威暴漲！\n" NOR);
    }

    // 施法訊息。
    action = sp["action"];
    if( !stringp(action) ) action = "$N唸動咒文﹐一道紫雷激射向$n！";
    message_vision(action + "\n", me, target);

    // ── 元素引擎：依雷抗(apply/thunder_def)折算實傷﹐pierce 則穿抗直回 base ──
    elem = stringp(sp["elem"]) ? sp["elem"] : "thunder";
    damage = magic_element_damage(target, base, elem, sp["pierce"]);

    dtype = sp["type"]; if( !stringp(dtype) ) dtype = "雷殛";
    target->receive_damage(damage, me, me);

    // 神光雷削神(docs 神光雷「神傷 33%」)：依本次傷害 N% 削目標當前神。
    if( sp["drain_sen"] > 0 && objectp(target) && living(target) ) {
        int dn = damage * sp["drain_sen"] / 100;
        if( dn > 0 ) {
            target->consume_stat("sen", dn, me);
            message_vision(HIY "$n的神識被這道神光雷震得一陣渙散！" NOR "\n", me, target);
        }
    }

    COMBAT_D->report_status(target);

    // 練法術技能 + 精熟（僅玩家）。
    if( userp(me) )
        me->improve_skill(sk, 1 + random(2));

    // 吟誦/運法後短暫無法行動(各式 delay﹐無則沿基底 2)。
    busy = sp["delay"]; if( busy <= 0 ) busy = 2;
    me->start_busy(busy);

    return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
