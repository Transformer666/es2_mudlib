// 天師道法【罡風咒】 taoism-wind -- 天師派玄衣弟子的入門風術
//
// 這是一門法術(magic)技能﹐天師派玄衣(風)分支的根本道法。本檔比照
// 素衣冰咒 daemon (taoism-freeze.c) 的結構建立﹐使技能可被指派與習練。
//
// === 具名咒 cast(2026-06-05 接通元素-效果引擎) ===
// docs/03-門派與武功/02-道士-天師與茅山.md「玄衣派(風)— taoism-storm」(L104)
// 風符四式逐項對齊﹐以本檔既有三式承載 docs 效果(同火/冰範式﹐elem="wind")：
//   docs 疾風  quick storm  25% (條件足時下次三重催咒) → 風刃(入門﹐附「催咒」提示)
//   docs 暴風  crazy storm  33% (命中忽視風抗)        → 玄風裂脈(pierce 穿風抗)
//   docs 轉輪大風 whirl storm 125%/delay 3            → 青龍御風(高耗、施後 delay 3)
// 風術為「純風元素傷害」一系﹐故各式 elem="wind"﹐傷害一律經
// /std/magic.c::magic_element_damage 折算對象風抗(apply/wind_def)。本檔
// override cast_spell：沿用 /std/magic 基底之全部驗證(神/距離/和平房/開戰/
// 練技/吟誦)﹐僅將「傷害套用」改走引擎(穿抗 + 風抗折算)並補各式具名特效。

#include <ansi.h>

inherit "/std/magic";

mapping *actions = ({
  ([
    "action":		"$N口誦真言﹐指尖一捲罡風射向$n的$l",
    "dodge":		5,
    "damage":		5,
    "damage_type":	"風傷"
  ]),
  ([
    "action":		"$N掐訣引風﹐一道罡氣捲向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"風傷"
  ]),
  ([
    "action":		"$N袖中玄符鼓盪﹐化作一片風刃罩向$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"風傷"
  ]),
  ([
    "action":		"$N凝神運法﹐一式『玄風裂脈』激射$n的$l",
    "dodge":		-15,
    "damage":		10,
    "damage_type":	"風傷"
  ]),
  ([
    "action":		"$N揮手撒出一蓬風絮﹐密密麻麻地捲向$n的$l",
    "dodge":		-10,
    "damage":		5,
    "damage_type":	"風傷"
  ]),
  ([
    "action":		"$N足踏罡步﹐一道風龍盤旋著撲向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"風傷"
  ]),
  ([
    "action":		"$N後退半步﹐凝起一團罡風轟向$n的$l",
    "dodge":		10,
    "damage":		5,
    "damage_type":	"風傷"
  ]),
  ([
    "action":		"$N雙掌一推﹐一式『青龍御風』狂飆暴卷﹐席捲$n的$l",
    "dodge":		0,
    "damage":		10,
    "damage_type":	"風傷"
  ]),
});

string *interattack = ({
  "$N默運風訣﹐指間隱隱透出一縷罡芒﹐靜待施法的時機。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("taoism-wind");
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

  damage = COMBAT_D->fight(me, opponent, "taoism-wind", actions[random(sizeof(actions))], weapon);
}

// ── 主動施法(cast)：本門咒文表 + 技能名（valid_enable 由 /std/magic 提供；
//    cast_spell 於本檔 override 以接通元素-效果引擎）──
string magic_skill() { return "taoism-wind"; }

// 前置宣告(lesson #12：定義前引用之函式一律先前置宣告﹐免編譯 Undefined
// function / daemon lazy-load 靜默失敗回 DAEMON_D 自身)。
varargs int cast_spell(object me, string spl, object target);

// 風符具名咒(docs L104「玄衣派(風)— taoism-storm」風符四式)。各式 elem="wind"﹐
// 傷害經 magic_element_damage 折算風抗(apply/wind_def)。效果旗標(供本檔 override 讀)：
//   "pierce":1     命中忽視風抗(docs 暴風 crazy storm「命中忽視風抗」)。
//   "multicast":1  施法後提示「催咒」可期(docs 疾風「條件足時下次三重催咒」)。
//   "delay":N      施法者施後 start_busy N(無則沿基底 2；docs 轉輪大風 delay 3)。
mapping query_spells()
{
  return ([
    // 疾風 quick storm：入門風刃﹐附「催咒」氣象提示(docs 疾風 25%/三重催咒)。
    "風刃" :     ([ "id":"fengren", "sen":10, "power":10, "type":"罡風",
        "elem":"wind", "delay":1, "multicast":1,
        "action":HIG "$N口誦真言﹐掐訣一引﹐一片鋒銳的風刃脫手飛出﹐「咻」地割向$n！" NOR ]),
    // 暴風 crazy storm：命中忽視風抗(docs 暴風 33%/忽視風抗)。
    "玄風裂脈" : ([ "id":"xuanfeng","sen":16, "power":20, "type":"罡風",
        "elem":"wind", "delay":1, "pierce":1,
        "action":HIG "$N足踏罡步﹐袖中玄符鼓盪﹐一式『玄風裂脈』化作罡氣風刃﹐無視罡風護體激射$n！" NOR ]),
    // 轉輪大風 whirl storm：高耗大威﹐施後吟誦較久(docs 轉輪大風 125%/delay 3)。
    "青龍御風" : ([ "id":"qinglong","sen":30, "power":40, "type":"罡風",
        "elem":"wind", "delay":3,
        "action":HIG "$N凝神運法﹐周身罡風暴漲﹐一式『青龍御風』狂飆沖天暴卷﹐當頭捲向$n！" NOR ]),
  ]);
}

// ── override cast_spell：沿用 /std/magic 基底驗證流程﹐傷害改走元素引擎 ──
// 與 /std/magic.c::cast_spell 同序(驗證→開戰→消神→燃符→傷害→練技→吟誦)﹐
// 僅「傷害套用」一步改為：magic_element_damage(target, base, "wind", pierce)
// 折算風抗(穿抗式直回 base)﹐並補各式具名特效(催咒提示 / 施後 delay)。
varargs int
cast_spell(object me, string spl, object target)
{
    mapping spells, sp;
    string sk, nm, action, dtype, elem;
    int cost, power, skill, base, damage, busy;
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

    // 符(talisman)消耗檢查(風符未標 fu﹐此段略過；保留以與基底契約一致)。
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
    base += random(base / 2 + 1);

    // 施法訊息。
    action = sp["action"];
    if( !stringp(action) ) action = "$N唸動咒文﹐一道罡風激射向$n！";
    message_vision(action + "\n", me, target);

    // ── 元素引擎：依風抗(apply/wind_def)折算實傷﹐pierce 則穿抗直回 base ──
    elem = stringp(sp["elem"]) ? sp["elem"] : "wind";
    damage = magic_element_damage(target, base, elem, sp["pierce"]);

    dtype = sp["type"]; if( !stringp(dtype) ) dtype = "罡風";
    target->receive_damage(damage, me, me);
    COMBAT_D->report_status(target);

    // 催咒提示(docs 疾風「條件足時下次三重催咒」)：技高者氣象更盛。僅提示﹐
    // 不臆造多重催咒機制(屬未接的咒文技巧系統﹐待 docs 咒文技巧公式定案)。
    if( sp["multicast"] && userp(me) && skill >= 50 )
        tell_object(me, HIG "你罡風咒法漸入化境﹐隱隱有催動三重罡風之兆。\n" NOR);

    // 練法術技能 + 精熟（僅玩家）。
    if( userp(me) )
        me->improve_skill(sk, 1 + random(2));

    // 吟誦/運法後短暫無法行動(各式 delay﹐無則沿基底 2)。
    busy = sp["delay"]; if( busy <= 0 ) busy = 2;
    me->start_busy(busy);

    return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
