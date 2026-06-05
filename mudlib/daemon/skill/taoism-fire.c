// 天師道法【火術】 taoism-fire -- 天師派朱衣弟子的入門火術
//
// 這是一門法術(magic)技能﹐天師派朱衣(火)分支的根本道法。本檔比照武功招式
// daemon (sword.c/lunmay.c) 的結構建立﹐使技能可被指派與習練(attack_using)﹐
// 並接上主動施法(cast)：query_spells() 列具名咒、override cast_spell() 依
// docs(03-門派與武功/02-道士-天師與茅山.md「朱衣派(火)→ taoism-fire」)的
// sen/delay/傷害%/特效逐式施展。
//
// 元素傷害走 /std/magic 引擎：magic_element_damage(victim,base,"fire",ignore)
// 折算抗性後﹐以 victim->receive_damage(dmg,me,me) 施加(與物理攻擊同終點﹐
// 消氣 kee)。各咒之 base = docs 傷害% × 法術力道(力道公式同 /std/magic 基底
// cast_spell：power*(100+skill)/100 + random)。地火另呼 magic_recover_onhit
// 回補施法者當前精氣神(docs：恢復氣)。
//
// 火術四式(docs L81-86)：
//   咒火   magic   sen 5  delay 1  傷害 50%。
//   地火   earth   sen 20 delay 1  傷害 33%(無視抗性、命中後回補施法者)。
//   大業火 inferno sen 45 delay 2  傷害 50% + 目標「當前氣」25%(穿防附加)。
//   三昧真火 pure  sen 75 delay 3  總傷害 300%(力道×300%)。

#include <ansi.h>

inherit "/std/magic";

// 各咒參數集中於此便於平衡微調。力道基數(power)取與既有簡式咒同量級﹔
// docs 傷害%(pct)套於力道之上。sen/delay/element 一律對齊 docs L81-86。
#define TF_ELEM             "fire"

// 力道基數(供既有 cast_spell 力道公式 power*(100+skill)/100 用)。
#define TF_MAGIC_POWER      10
#define TF_EARTH_POWER      18
#define TF_INFERNO_POWER    24
#define TF_PURE_POWER       30

mapping *actions = ({
  ([
    "action":		"$N口誦真言﹐指尖一點火星撲向$n的$l",
    "dodge":		5,
    "damage":		5,
    "damage_type":	"灼傷"
  ]),
  ([
    "action":		"$N掐訣引火﹐一道火舌捲向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"灼傷"
  ]),
  ([
    "action":		"$N袖中朱符燃起﹐化作一團赤焰罩向$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"灼傷"
  ]),
  ([
    "action":		"$N凝神運法﹐一式『離火燎原』噴向$n的$l",
    "dodge":		-15,
    "damage":		10,
    "damage_type":	"灼傷"
  ]),
  ([
    "action":		"$N揮手撒出一蓬火星﹐密密麻麻地落向$n的$l",
    "dodge":		-10,
    "damage":		5,
    "damage_type":	"灼傷"
  ]),
  ([
    "action":		"$N足踏罡步﹐一道火龍盤旋著撲向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"灼傷"
  ]),
  ([
    "action":		"$N後退半步﹐凝起一團火球轟向$n的$l",
    "dodge":		10,
    "damage":		5,
    "damage_type":	"灼傷"
  ]),
  ([
    "action":		"$N雙掌一推﹐一式『朱雀焚天』烈焰沖天而起﹐席捲$n的$l",
    "dodge":		0,
    "damage":		10,
    "damage_type":	"灼傷"
  ]),
});

string *interattack = ({
  "$N默運火訣﹐指間隱隱透出一縷赤芒﹐靜待施法的時機。\n",
});

// ── 前置宣告(lesson #12：定義前引用之函式一律前置宣告)──────────────
// query_spells/magic_skill 為繼承 /std/magic 之覆寫(inherited)﹐恆可解析﹐
// 不另前置宣告(鏡 taoism-of-conviction.c)。下列為本檔覆寫/新增者。
varargs int    cast_spell(object me, string spl, object target);
private object tf_resolve_target(object me, object target);

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("taoism-fire");
  setup();
}

void
attack_using (object me, object opponent, object weapon)
{
  int damage;

  if (!opponent)
    {
      if (me->query_temp("last_attacked_target"))
	message_vision (RED + interattack[random(sizeof(interattack))] + NOR, me, weapon);
      return;
    }

  damage = COMBAT_D->fight(me, opponent, "taoism-fire", actions[random(sizeof(actions))], weapon);
}

// ── 主動施法(cast)：本門技能名與咒文表(valid_enable 由 /std/magic 提供)──
string magic_skill() { return "taoism-fire"; }

// 咒文表：id/sen/power(力道基數)/pct(docs 傷害%)/type/action。
// ignore=無視抗性﹔recover=命中回補施法者當前精氣神之百分比(docs「恢復氣」)﹔
// cur_kee=另加目標當前氣之百分比(穿防)﹔total_mult=力道直乘倍率(三昧真火 300%)。
mapping query_spells()
{
  return ([
    "咒火" :     ([ "id":"magic",   "sen":5,  "delay":1, "power":TF_MAGIC_POWER,   "pct":50,  "type":"灼傷",
        "action":HIR "$N口誦真言﹐掐訣一引﹐一團赤紅的咒火脫手飛出﹐「轟」地罩向$n！" NOR ]),
    "地火" :     ([ "id":"earth",   "sen":20, "delay":1, "power":TF_EARTH_POWER,   "pct":33,  "type":"灼傷",
        "ignore":1, "recover":100,
        "action":HIR "$N足踏罡步﹐引動地脈伏火﹐一式『地火』自$n足下噴湧而出﹐烈焰倒捲灼身！" NOR ]),
    "大業火" :   ([ "id":"inferno", "sen":45, "delay":2, "power":TF_INFERNO_POWER, "pct":50,  "type":"灼傷",
        "cur_kee":25,
        "action":HIR "$N凝神運法﹐周身真火暴漲﹐一式『大業火』赤焰沖天而起﹐當頭澆向$n！" NOR ]),
    "三昧真火" : ([ "id":"pure",    "sen":75, "delay":3, "power":TF_PURE_POWER,    "total_mult":300, "type":"灼傷",
        "action":HIR "$N默運九轉玄功﹐周身騰起無形業火﹐一式『三昧真火』焚盡萬法﹐三昧真火裹住$n！" NOR ]),
  ]);
}

// 取施法對象：未指定時取當前敵人首個(鏡 /std/magic 基底 cast_spell 之 query_enemy)。
private object
tf_resolve_target(object me, object target)
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
// 之後依咒分派傷害與特效。
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

  // 取施法對象並驗證。
  target = tf_resolve_target(me, target);
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

  // 各咒 base 傷害：三昧真火為力道直乘倍率(total_mult)﹐餘者為 docs 傷害%×力道。
  if( sp["total_mult"] )
    base = force * (int)sp["total_mult"] / 100;
  else
    base = force * (int)sp["pct"] / 100;

  // 大業火：另加目標「當前氣」之 cur_kee%(穿防附加)。
  if( sp["cur_kee"] )
    base += (int)target->query_stat("kee") * (int)sp["cur_kee"] / 100;

  // 元素傷害折算抗性(地火 ignore=1 穿防)。
  ignore = sp["ignore"] ? 1 : 0;
  dmg = magic_element_damage(target, base, TF_ELEM, ignore);

  // 施法訊息。
  action = sp["action"];
  if( !stringp(action) ) action = "$N唸動火咒﹐一道真火激射向$n！";
  message_vision(action + "\n", me, target);

  // 套用傷害(與物理攻擊同走 receive_damage﹐消氣 kee)。
  dtype = sp["type"]; if( !stringp(dtype) ) dtype = "灼傷";
  if( dmg > 0 ) {
    target->receive_damage(dmg, me, me);
    COMBAT_D->report_status(target);
  }

  // 地火：命中後依本次傷害回補施法者當前精氣神(docs「恢復氣」﹐引擎補 gin/kee/sen)。
  if( sp["recover"] && dmg > 0 )
    magic_recover_onhit(me, dmg, (int)sp["recover"]);

  // 練法術技能 + 精熟(僅玩家)。
  if( userp(me) )
    me->improve_skill(sk, 1 + random(2));

  // 吟誦/運法後短暫無法行動(施法時間 delay﹐對齊 docs)。
  me->start_busy(sp["delay"] ? (int)sp["delay"] : 1);

  return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
