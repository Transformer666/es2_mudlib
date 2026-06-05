// 天師道法【冰咒】 taoism-freeze -- 天師派素衣弟子的入門冰術
//
// 這是一門法術(magic)技能﹐天師派素衣(冰)分支的根本道法。本檔比照朱衣火術
// daemon (taoism-fire.c) 的結構建立﹐使技能可被指派與習練(attack_using)﹐並
// 接上主動施法(cast)：query_spells() 列具名咒、override cast_spell() 依 docs
// (03-門派與武功/02-道士-天師與茅山.md「素衣派(冰)→ taoism-freeze」L127-134)
// 的 sen/delay/傷害/效果逐式施展。
//
// 元素傷害走 /std/magic 引擎：magic_element_damage(victim,base,"freeze",ignore)
// 折算抗性後施加。各咒 base = docs 傷害% × 法術力道(力道公式同 /std/magic 基底
// cast_spell：power*(100+skill)/100 + random)。兆冰之精神傷與恢復、無相冰之
// 命中/失手 delay﹐各依 docs 另行處理。
//
// 冰咒四式(docs L127-134)：
//   寒冰     chill   sen 5  delay 1  傷害 50%。
//   兆冰     ominous sen 20 delay 2  精傷 100%、神傷 33%、恢復精神=傷害 50%(無視抗性)。
//   無相冰   shadow  sen 30 delay 0/3 命中無自身 delay、對目標 delay 3﹔失手自身 delay 1。
//   七重玄冰 polar   sen 50 delay 2  傷害 150%。

#include <ansi.h>

inherit "/std/magic";

// 各咒參數集中於此便於平衡微調。對齊 docs L127-134。
#define TZ_ELEM             "freeze"

// 力道基數(供既有 cast_spell 力道公式 power*(100+skill)/100 用)。
#define TZ_CHILL_POWER      10
#define TZ_OMINOUS_POWER    18
#define TZ_POLAR_POWER      26

// 兆冰：精傷% / 神傷% / 恢復精神(占本次精傷)% 。
#define TZ_OMINOUS_GIN      100
#define TZ_OMINOUS_SEN      33
#define TZ_OMINOUS_RECOVER  50

// 無相冰：命中時對目標之 delay / 失手時自身之 delay。
#define TZ_SHADOW_HIT_DELAY 3
#define TZ_SHADOW_MISS_DELAY 1

mapping *actions = ({
  ([
    "action":		"$N口誦真言﹐指尖一點寒星射向$n的$l",
    "dodge":		5,
    "damage":		5,
    "damage_type":	"寒傷"
  ]),
  ([
    "action":		"$N掐訣引冰﹐一道寒流捲向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"寒傷"
  ]),
  ([
    "action":		"$N袖中素符凝霜﹐化作一片冰晶罩向$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"寒傷"
  ]),
  ([
    "action":		"$N凝神運法﹐一式『玄冰封脈』激射$n的$l",
    "dodge":		-15,
    "damage":		10,
    "damage_type":	"寒傷"
  ]),
  ([
    "action":		"$N揮手撒出一蓬冰屑﹐密密麻麻地落向$n的$l",
    "dodge":		-10,
    "damage":		5,
    "damage_type":	"寒傷"
  ]),
  ([
    "action":		"$N足踏罡步﹐一道冰龍盤旋著撲向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"寒傷"
  ]),
  ([
    "action":		"$N後退半步﹐凝起一團寒珠轟向$n的$l",
    "dodge":		10,
    "damage":		5,
    "damage_type":	"寒傷"
  ]),
  ([
    "action":		"$N雙掌一推﹐一式『玄武凝寒』霜華暴卷﹐席捲$n的$l",
    "dodge":		0,
    "damage":		10,
    "damage_type":	"寒傷"
  ]),
});

string *interattack = ({
  "$N默運冰訣﹐指間隱隱透出一縷寒芒﹐靜待施法的時機。\n",
});

// ── 前置宣告(lesson #12：定義前引用之函式一律前置宣告)──────────────
// query_spells/magic_skill 為繼承 /std/magic 之覆寫(inherited)﹐恆可解析﹐
// 不另前置宣告(鏡 taoism-of-conviction.c)。下列為本檔覆寫/新增者。
varargs int    cast_spell(object me, string spl, object target);
private object tz_resolve_target(object me, object target);
private int    magic_shadow_chance(int skill, int level);

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("taoism-freeze");
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

  damage = COMBAT_D->fight(me, opponent, "taoism-freeze", actions[random(sizeof(actions))], weapon);
}

// ── 主動施法(cast)：本門技能名與咒文表(valid_enable 由 /std/magic 提供)──
string magic_skill() { return "taoism-freeze"; }

// 咒文表：id/sen/delay/power(力道基數)/pct(docs 傷害%)/type/action。
// kind 區分特殊式：ominous(精神傷+恢復)、shadow(控場無傷)﹐餘者為單純元素傷。
mapping query_spells()
{
  return ([
    "寒冰" :     ([ "id":"chill",   "sen":5,  "delay":1, "power":TZ_CHILL_POWER, "pct":50, "type":"寒傷",
        "action":HIC "$N口誦真言﹐掐訣一引﹐一點晶瑩的寒冰脫手飛出﹐「嗤」地射向$n！" NOR ]),
    "兆冰" :     ([ "id":"ominous", "sen":20, "delay":2, "power":TZ_OMINOUS_POWER, "kind":"ominous", "type":"凍傷",
        "action":HIC "$N足踏罡步﹐袖中素符凝霜﹐一式『兆冰』化作森寒冰魄﹐直透$n識海﹐凍其精魂！" NOR ]),
    "無相冰" :   ([ "id":"shadow",  "sen":30, "delay":0, "kind":"shadow", "type":"凍傷",
        "action":HIW "$N斂去形跡﹐一式『無相冰』無聲無息地自虛空凝結﹐霜華暴卷而封$n！" NOR ]),
    "七重玄冰" : ([ "id":"polar",   "sen":50, "delay":2, "power":TZ_POLAR_POWER, "pct":150, "type":"凍傷", "effect":"freeze",
        "action":HIW "$N凝神運法﹐周身寒氣暴漲﹐一式『七重玄冰』七重霜華沖天暴卷﹐當頭澆向$n﹐將其凍封當場！" NOR ]),
  ]);
}

// 取施法對象：未指定時取當前敵人首個(鏡 /std/magic 基底 cast_spell 之 query_enemy)。
private object
tz_resolve_target(object me, object target)
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
// 驗證流程鏡 /std/magic 基底 cast_spell﹐之後依咒分派傷害與特效。
varargs int
cast_spell(object me, string spl, object target)
{
  mapping spells, sp;
  string sk, nm, action, dtype, kind;
  int cost, force, skill, base, dmg, gin_dmg, sen_dmg, recover, hit;

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
  target = tz_resolve_target(me, target);
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

  // 施法訊息(先出咒象)。
  action = sp["action"];
  if( !stringp(action) ) action = "$N唸動冰咒﹐一道寒氣激射向$n！";
  message_vision(action + "\n", me, target);

  kind = sp["kind"];

  // ── 無相冰(shadow)：控場無傷。命中→自身無 delay、目標 delay 3﹔失手→自身 delay 1。
  if( kind == "shadow" ) {
    // 命中判定：以本門技能對抗目標等級﹐技能越高越易命中(夾 5%..95%)。
    skill = me->query_skill(sk);
    hit = random(100) < magic_shadow_chance(skill, (int)target->query_level());
    if( hit ) {
      message_vision(HIW "$n被無相寒冰自虛空封住周身氣脈，竟連動也動不得！" NOR "\n", me, target);
      magic_delay(target, TZ_SHADOW_HIT_DELAY);
      // 命中無自身 delay(docs delay 0)。
    } else {
      message_vision(HIC "$N這一式無相冰未能凝實，寒氣消散，自身一陣氣滯。" NOR "\n", me, target);
      me->start_busy(TZ_SHADOW_MISS_DELAY);
    }
    if( userp(me) )
      me->improve_skill(sk, 1 + random(2));
    return 1;
  }

  // 力道：神/技能驅動(公式同 /std/magic 基底 cast_spell)。
  skill = me->query_skill(sk);
  force = (int)sp["power"] * (100 + skill) / 100;
  force += random(force / 2 + 1);

  dtype = sp["type"]; if( !stringp(dtype) ) dtype = "凍傷";

  // ── 兆冰(ominous)：精傷 100%、神傷 33%、恢復精神=精傷 50%、無視抗性(穿防)。
  if( kind == "ominous" ) {
    // 精傷=力道×100%(無視抗性)。神傷=精傷×33%。
    gin_dmg = magic_element_damage(target, force * TZ_OMINOUS_GIN / 100, TZ_ELEM, 1);
    sen_dmg = gin_dmg * TZ_OMINOUS_SEN / 100;
    if( gin_dmg > 0 ) target->consume_stat("gin", gin_dmg, me);
    if( sen_dmg > 0 ) target->consume_stat("sen", sen_dmg, me);
    COMBAT_D->report_status(target);
    // 恢復施法者精神(gin/sen)當前值=精傷 50%。
    recover = gin_dmg * TZ_OMINOUS_RECOVER / 100;
    if( recover > 0 ) {
      me->supplement_stat("gin", recover);
      me->supplement_stat("sen", recover);
      message_vision(HIC "$N納寒回元，森森冰氣化作精神﹐倒灌己身識海。" NOR "\n", me, target);
    }
    if( userp(me) )
      me->improve_skill(sk, 1 + random(2));
    me->start_busy(sp["delay"] ? (int)sp["delay"] : 2);
    return 1;
  }

  // ── 寒冰 / 七重玄冰：單純元素傷(走 receive_damage﹐消氣 kee)。
  base = force * (int)sp["pct"] / 100;
  dmg = magic_element_damage(target, base, TZ_ELEM, 0);
  if( dmg > 0 ) {
    target->receive_damage(dmg, me, me);
    COMBAT_D->report_status(target);
  }

  // 特效：freeze → 對象短暫無法行動(七重玄冰)。
  if( sp["effect"] == "freeze" && objectp(target) && living(target)
  && !target->is_busy() ) {
    message_vision(HIC "$n被森森寒氣凍得周身一滯，動作為之一頓！" NOR "\n", me, target);
    magic_delay(target, 1);
  }

  if( userp(me) )
    me->improve_skill(sk, 1 + random(2));

  me->start_busy(sp["delay"] ? (int)sp["delay"] : 1);

  return 1;
}

// 無相冰命中率：技能越高越易命中、目標等級越高越難。夾於 5%..95%。
private int
magic_shadow_chance(int skill, int level)
{
  int c;

  c = 50 + (skill - level) / 2;
  if( c < 5 ) c = 5;
  if( c > 95 ) c = 95;
  return c;
}

// vim: set ts=4 sw=4 syntax=lpc
