// 天師道法【風符】 taoism-wind -- 天師派玄衣弟子的入門風術
//
// 這是一門法術(magic)技能﹐天師派玄衣(風)分支的根本道法。本檔比照已 live 驗
// 正確之 taoism-fire.c 的結構建立﹐使技能可被指派與習練(attack_using)﹐並接上
// 主動施法(cast)：query_spells() 列具名咒、override cast_spell() 依
// docs(03-門派與武功/02-道士-天師與茅山.md「玄衣派(風)→ taoism-storm」L104-111)
// 的咒名/sen/delay/傷害%/特效逐式施展。
//
// 元素傷害走 /std/magic 引擎：magic_element_damage(victim,base,"wind",ignore)
// 折算對象風抗(apply/wind_def)後﹐以 victim->receive_damage(dmg,me,me) 施加
// (與物理攻擊同終點﹐消氣 kee)。各咒之 base = docs 傷害% × 法術力道(力道公式同
// /std/magic 基底 cast_spell：power*(100+skill)/100 + random)。
//
// 風符四式(docs L108-111﹐咒名/sen/delay/傷害% 嚴格對齊)：
//   疾風     quick storm  sen 10 delay 1  傷害 25%(技能滿足條件下次必三重催咒)。
//   暴風     crazy storm  sen 30 delay 1  傷害 33%(命中時忽視風抗)。
//   飛戮風   killer storm sen 50 delay 1  傷害 75%。
//   轉輪大風 whirl storm  sen 75 delay 3  傷害 125%。

#include <ansi.h>

inherit "/std/magic";

// 各咒參數集中於此便於平衡微調。力道基數(power)取與既有簡式咒同量級﹔
// docs 傷害%(pct)套於力道之上。sen/delay/element 一律對齊 docs L108-111。
#define TW_ELEM             "wind"

// 力道基數(供既有 cast_spell 力道公式 power*(100+skill)/100 用)。
#define TW_QUICK_POWER      10
#define TW_CRAZY_POWER      18
#define TW_KILLER_POWER     24
#define TW_WHIRL_POWER      30

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
    "action":		"$N凝神運法﹐一式『飛戮風』激射$n的$l",
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
    "action":		"$N雙掌一推﹐一式『轉輪大風』狂飆暴卷﹐席捲$n的$l",
    "dodge":		0,
    "damage":		10,
    "damage_type":	"風傷"
  ]),
});

string *interattack = ({
  "$N默運風訣﹐指間隱隱透出一縷罡芒﹐靜待施法的時機。\n",
});

// ── 前置宣告(lesson #12：定義前引用之函式一律前置宣告)──────────────
// query_spells/magic_skill 為繼承 /std/magic 之覆寫(inherited)﹐恆可解析﹐
// 不另前置宣告(鏡 taoism-fire.c)。下列為本檔覆寫/新增者。
varargs int    cast_spell(object me, string spl, object target);
private object tw_resolve_target(object me, object target);

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

// ── 主動施法(cast)：本門技能名與咒文表(valid_enable 由 /std/magic 提供)──
string magic_skill() { return "taoism-wind"; }

// 咒文表：id/sen/delay/power(力道基數)/pct(docs 傷害%)/type/action。
// pierce=命中忽視風抗(docs 暴風「命中時忽視風抗」)﹔
// multicast=施後氣象提示(docs 疾風「技能滿足條件下次必三重催咒」之氣象鋪陳)。
// sen/delay/pct 一律嚴格對齊 docs L108-111。
mapping query_spells()
{
  return ([
    "疾風" :     ([ "id":"quick",  "sen":10, "delay":1, "power":TW_QUICK_POWER,  "pct":25,  "type":"風傷",
        "multicast":1,
        "action":HIG "$N口誦真言﹐掐訣一引﹐一陣疾風脫手飛出﹐「咻」地割向$n！" NOR ]),
    "暴風" :     ([ "id":"crazy",  "sen":30, "delay":1, "power":TW_CRAZY_POWER,  "pct":33,  "type":"風傷",
        "pierce":1,
        "action":HIG "$N足踏罡步﹐袖中玄符鼓盪﹐一式『暴風』化作罡氣風刃﹐無視罡風護體激射$n！" NOR ]),
    "飛戮風" :   ([ "id":"killer", "sen":50, "delay":1, "power":TW_KILLER_POWER, "pct":75,  "type":"風傷",
        "action":HIG "$N凝神運法﹐周身罡風暴漲﹐一式『飛戮風』化作千百道風刃﹐鋪天蓋地戮向$n！" NOR ]),
    "轉輪大風" : ([ "id":"whirl",  "sen":75, "delay":3, "power":TW_WHIRL_POWER,  "pct":125, "type":"風傷",
        "action":HIG "$N默運玄功﹐周身狂飆暴卷﹐一式『轉輪大風』狂風如輪沖天暴捲﹐當頭捲向$n！" NOR ]),
  ]);
}

// 取施法對象：未指定時取當前敵人首個(鏡 /std/magic 基底 cast_spell 之 query_enemy)。
private object
tw_resolve_target(object me, object target)
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

// override cast_spell：依本門具名咒之 docs 規格施展(元素傷害走 /std/magic 引擎)。
// 驗證流程鏡 /std/magic 基底 cast_spell(sen 檢查、對象檢查、no_fight、開戰串接)﹐
// 之後依咒分派傷害與特效。未命中本門咒名/id 者落回 ::cast_spell(/std/magic 基底)。
varargs int
cast_spell(object me, string spl, object target)
{
  mapping spells, sp;
  string sk, nm, action, dtype;
  int cost, force, skill, base, dmg, ignore;

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
  target = tw_resolve_target(me, target);
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

  // 元素傷害折算抗性(暴風 pierce=1 穿風抗直回 base)。
  ignore = sp["pierce"] ? 1 : 0;
  dmg = magic_element_damage(target, base, TW_ELEM, ignore);

  // 施法訊息。
  action = sp["action"];
  if( !stringp(action) ) action = "$N唸動風咒﹐一道罡風激射向$n！";
  message_vision(action + "\n", me, target);

  // 套用傷害(與物理攻擊同走 receive_damage﹐消氣 kee)。
  dtype = sp["type"]; if( !stringp(dtype) ) dtype = "風傷";
  if( dmg > 0 ) {
    target->receive_damage(dmg, me, me);
    COMBAT_D->report_status(target);
  }

  // 催咒提示(docs 疾風「技能滿足條件下次必三重催咒」)：技高者氣象更盛。僅提示﹐
  // 不臆造多重催咒機制(屬未接的咒文技巧系統﹐待 docs 咒文技巧公式定案)。
  if( sp["multicast"] && userp(me) && skill >= 50 )
    tell_object(me, HIG "你罡風咒法漸入化境﹐隱隱有催動三重罡風之兆。\n" NOR);

  // 練法術技能 + 精熟(僅玩家)。
  if( userp(me) )
    me->improve_skill(sk, 1 + random(2));

  // 吟誦/運法後短暫無法行動(施法時間 delay﹐對齊 docs)。
  me->start_busy(sp["delay"] ? (int)sp["delay"] : 1);

  return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
