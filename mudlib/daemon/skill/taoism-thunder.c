// 天師道法【雷法】 taoism-thunder -- 天師派紫衣弟子的入門雷術
//
// 這是一門法術(magic)技能﹐天師派紫衣(雷)分支的根本道法。本檔比照已 live 驗
// 正確之 taoism-fire.c 的結構建立﹐使技能可被指派與習練(attack_using)﹐並接上
// 主動施法(cast)：query_spells() 列具名咒、override cast_spell() 依
// docs(03-門派與武功/02-道士-天師與茅山.md「紫衣派(雷)→ taoism-thunder」L150-157)
// 的咒名/sen/delay/傷害%/特效逐式施展。
//
// 元素傷害走 /std/magic 引擎：magic_element_damage(victim,base,"thunder",ignore)
// 折算對象雷抗(apply/thunder_def)後﹐以 victim->receive_damage(dmg,me,me) 施加
// (與物理攻擊同終點﹐消氣 kee)。各咒之 base = docs 傷害% × 法術力道(力道公式同
// /std/magic 基底 cast_spell：power*(100+skill)/100 + random)。
//
// 雷法四式(docs L154-157﹐咒名/sen/delay/傷害% 嚴格對齊)：
//   澤雷     swamp thunder    sen 5  delay 1  傷害 50%。
//   爆雷     blaster thunder  sen 50 delay 1  傷害 25% + 目標當前神 1/8(穿防附加)。
//   神光雷   divine thunder   sen 75 delay 2  目標神傷 33%(無視抗性、削目標神識)。
//   六卦熒雷 hexagram thunder sen 90 delay 2  傷害 175%(觸發 overload 加成但不消耗)。
//
// === 九龍超載 overload(docs L163 + daemon/skill/nine-dragon_force.c 旗標契約)===
// nine-dragon_force.c::do_overload 立下旗標 me->query_temp("force/taoism_overload")
//   (= 50)﹐表「下次天師咒基礎傷害 +50%」。本檔施咒前讀此旗標：基礎傷害
//   先 ×1.5﹐再 delete_temp 清旗標(僅及「下次」一道)。docs 六卦熒雷
//   「觸發但不消耗 overload」之旗標 → 本表以 "keep_overload":1 標記(該式吃加成
//   但不清旗標)﹔其餘三式均屬「吃加成並清旗標」之常態。

#include <ansi.h>

inherit "/std/magic";

// 各咒參數集中於此便於平衡微調。力道基數(power)取與既有簡式咒同量級﹔
// docs 傷害%(pct)套於力道之上。sen/delay/element 一律對齊 docs L154-157。
#define TT_ELEM             "thunder"

// 九龍超載旗標 key(鏡 daemon/skill/nine-dragon_force.c 之契約﹐毋直接 include
// 其檔﹔此處複述常數以對齊。do_overload set_temp(key, 50)﹐cast 端讀後 delete_temp)。
#define NDF_OVERLOAD_TEMP   "force/taoism_overload"

// 力道基數(供既有 cast_spell 力道公式 power*(100+skill)/100 用)。
#define TT_SWAMP_POWER      10
#define TT_BLASTER_POWER    16
#define TT_DIVINE_POWER     30
#define TT_HEXAGRAM_POWER   34

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
    "action":		"$N凝神運法﹐一式『神光雷』激射$n的$l",
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
    "action":		"$N雙掌一推﹐一式『六卦熒雷』霹靂暴鳴﹐席捲$n的$l",
    "dodge":		0,
    "damage":		10,
    "damage_type":	"雷傷"
  ]),
});

string *interattack = ({
  "$N默運雷訣﹐指間隱隱透出一縷紫芒﹐靜待施法的時機。\n",
});

// ── 前置宣告(lesson #12：定義前引用之函式一律前置宣告)──────────────
// query_spells/magic_skill 為繼承 /std/magic 之覆寫(inherited)﹐恆可解析﹐
// 不另前置宣告(鏡 taoism-fire.c)。下列為本檔覆寫/新增者。
varargs int    cast_spell(object me, string spl, object target);
private object tt_resolve_target(object me, object target);

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

// ── 主動施法(cast)：本門技能名與咒文表(valid_enable 由 /std/magic 提供)──
string magic_skill() { return "taoism-thunder"; }

// 咒文表：id/sen/delay/power(力道基數)/pct(docs 傷害%)/type/action。各式 elem 恆 thunder。
//   "ignore":1        命中忽視雷抗(docs 神光雷「無視抗性」)。
//   "cur_sen_frac":N  另加目標「當前神」之 1/N(docs 爆雷「+ 當前神 1/8」﹐N=8﹐穿防)。
//   "drain_sen":N     對目標削神(consume_stat "sen")= 本次傷害 N%(docs 神光雷「神傷 33%」)。
//   "keep_overload":1 吃九龍超載加成但不清旗標(docs 六卦熒雷「觸發但不消耗 overload」)。
// sen/delay/pct 一律嚴格對齊 docs L154-157。
mapping query_spells()
{
  return ([
    "澤雷" :     ([ "id":"swamp",    "sen":5,  "delay":1, "power":TT_SWAMP_POWER,    "pct":50,  "type":"雷殛",
        "action":HIY "$N口誦真言﹐掐訣一引﹐一道澤雷脫手飛出﹐「霹」地轟向$n！" NOR ]),
    "爆雷" :     ([ "id":"blaster",  "sen":50, "delay":1, "power":TT_BLASTER_POWER,  "pct":25,  "type":"雷殛",
        "cur_sen_frac":8,
        "action":HIY "$N足踏罡步﹐袖中紫符鼓盪﹐一式『爆雷』盡引周身神識化作雷網紫電﹐激射$n！" NOR ]),
    "神光雷" :   ([ "id":"divine",   "sen":75, "delay":2, "power":TT_DIVINE_POWER,   "pct":50,  "type":"雷殛",
        "ignore":1, "drain_sen":33,
        "action":HIY "$N凝神運法﹐周身雷光暴漲﹐一式『神光雷』神光霹靂沖天暴鳴﹐當頭劈向$n！" NOR ]),
    "六卦熒雷" : ([ "id":"hexagram", "sen":90, "delay":2, "power":TT_HEXAGRAM_POWER, "pct":175, "type":"雷殛",
        "keep_overload":1,
        "action":HIY "$N默運九龍神功﹐六卦交感引動九霄熒雷﹐一式『六卦熒雷』霹靂貫空﹐萬鈞雷霆轟落$n！" NOR ]),
  ]);
}

// 取施法對象：未指定時取當前敵人首個(鏡 /std/magic 基底 cast_spell 之 query_enemy)。
private object
tt_resolve_target(object me, object target)
{
  object *es;

  if( objectp(target) ) return target;
  es = me->query_enemy();
  if( arrayp(es) ) {
    es -= ({ 0 });
    if( sizeof(es) ) return es[0];
  }
  return 0;
}

// override cast_spell：依本門具名咒之 docs 規格施展(元素傷害走 /std/magic 引擎)﹐
// 並接通九龍超載(下次基礎傷 +50%)。未命中本門咒名/id 者落回 ::cast_spell(基底)。
varargs int
cast_spell(object me, string spl, object target)
{
  mapping spells, sp;
  string sk, nm, action, dtype;
  int cost, force, skill, base, dmg, ignore, overload;

  if( !objectp(me) || !stringp(spl) ) return 0;

  sk = magic_skill();
  spells = query_spells();
  if( !sk || !mapp(spells) || !sizeof(spells) ) {
    notify_fail("你還沒有可施展的法術。\n");
    return 0;
  }

  // 找咒文：先比中文名、再比英文 id。未命中則落回基底 cast_spell。
  sp = spells[spl];
  if( !mapp(sp) ) foreach( nm, mapping m in spells )
    if( mapp(m) && m["id"] == spl ) { sp = m; break; }
  if( !mapp(sp) )
    return ::cast_spell(me, spl, target);

  // 須已習得本門法術。
  if( me->query_skill(sk) <= 0 && !me->query_learn(sk) ) {
    notify_fail("你並未習得「" + to_chinese(sk) + "」。\n");
    return 0;
  }

  // 取施法對象並驗證。
  target = tt_resolve_target(me, target);
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

  // 非戰之地不可施展攻擊法術(與基底 cast_spell / combatd.c 規則一致)。
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

  // ── 通過所有檢查，正式施法(之後不再失敗)──
  if( !me->is_fighting(target) ) {
    me->kill_ob(target);
    if( userp(target) ) target->fight_ob(me);
    else target->kill_ob(me);
  }

  me->consume_stat("sen", cost);

  // 力道：神/技能驅動(公式同 /std/magic 基底 cast_spell)。
  skill = me->query_skill(sk);
  force = (int)sp["power"] * (100 + skill) / 100;
  force += random(force / 2 + 1);

  // base 傷害：docs 傷害%(pct)×力道。
  base = force * (int)sp["pct"] / 100;

  // 爆雷蓄能：另加目標「當前神」之 1/N(docs 爆雷「+ 當前神 1/8」﹐穿防附加)。
  if( sp["cur_sen_frac"] )
    base += (int)target->query_stat("sen") / (int)sp["cur_sen_frac"];

  // ── 九龍超載(docs L163)：旗標非 0 則基礎傷 ×(1+該百分比)﹐用後清旗標 ──
  // (六卦熒雷類 "keep_overload":1 之式吃加成但不清﹔其餘三式吃加成並清旗標)。
  overload = (int)me->query_temp(NDF_OVERLOAD_TEMP);
  if( overload > 0 ) {
    base = base * (100 + overload) / 100;
    if( !sp["keep_overload"] )
      me->delete_temp(NDF_OVERLOAD_TEMP);
    tell_object(me, HIM "你周身蓄勢的雷龍轟然爆發﹐這一道天師咒雷威暴漲！\n" NOR);
  }

  // 元素傷害折算抗性(神光雷 ignore=1 穿雷抗直回 base)。
  ignore = sp["ignore"] ? 1 : 0;
  dmg = magic_element_damage(target, base, TT_ELEM, ignore);

  // 施法訊息。
  action = sp["action"];
  if( !stringp(action) ) action = "$N唸動雷咒﹐一道紫雷激射向$n！";
  message_vision(action + "\n", me, target);

  // 套用傷害(與物理攻擊同走 receive_damage﹐消氣 kee)。
  dtype = sp["type"]; if( !stringp(dtype) ) dtype = "雷殛";
  if( dmg > 0 ) {
    target->receive_damage(dmg, me, me);
    COMBAT_D->report_status(target);
  }

  // 神光雷削神(docs 神光雷「目標神傷 33%」)：依本次傷害 N% 削目標當前神。
  if( sp["drain_sen"] && dmg > 0 && objectp(target) && living(target) ) {
    int dn = dmg * (int)sp["drain_sen"] / 100;
    if( dn > 0 ) {
      target->consume_stat("sen", dn, me);
      message_vision(HIY "$n的神識被這道神光雷震得一陣渙散！" NOR "\n", me, target);
    }
  }

  // 練法術技能 + 精熟(僅玩家)。
  if( userp(me) )
    me->improve_skill(sk, 1 + random(2));

  // 吟誦/運法後短暫無法行動(施法時間 delay﹐對齊 docs)。
  me->start_busy(sp["delay"] ? (int)sp["delay"] : 1);

  return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
