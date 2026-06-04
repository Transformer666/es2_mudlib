// 武陀灸術【引源針法】 potency-needle -- 武陀灸堂的狀態強化針法
//
// 武陀灸堂一脈的輔助針術(docs/03-門派與武功/07-方士-龍圖武陀.md L62、
// docs/02-遊戲系統與機制/06-煉丹與書本系統.md L101)：「fatigue 緩疲勞﹔
// awareness 強警﹔move 強動﹔element 強元素﹔強警/強元素/強動不可同時」。
// 引源者﹐引動體內源氣以強化各種狀態。基礎技能型別為 needle (針術)﹐
// 見 feature/weapon/needle.c。
//
// 灸術派發鏈(同 amazing-needle.c)：玩家 `enable cauterization with potency-needle`
// 後﹐`acupuncture awareness to <目標>` 經 cmds/std/acupuncture.c 取
// skill_mapped("cauterization")(=「potency-needle」)﹐呼
// SKILL_D("potency-needle")->acupuncture_cauterization(me, "awareness", target)。
// 簽名嚴格依該指令殼。func 為去空白後的灸術名。
//
// 各引源效果(對應 feature/char/combat.c::query_ability 的 apply 鍵)：
//   fatigue   緩疲勞 -- 削目標 fatigue 現值(consume_stat fatigue)﹐紓緩疲勞。
//   awareness 強警   -- add_temp apply/awarness(注﹕engine 鍵拼作 "awarness"﹐
//                       見 combat.c L128/131﹐須照拼方能生效)。
//   move      強動   -- add_temp apply/move(行動力﹐combat.c L119-122)。
//   element   強元素 -- add_temp apply/armor_vs_fire(元素抗性﹐見 race/yenhold.c)。
//   docs：強警/強元素/強動三者不可同時(對同目標互斥)﹔fatigue 不受此限。
//
// runtime 鐵則：不涉 ::die()/destruct()(#10)、不 replace_program(#11)﹔針法 daemon
// (inherit SKILL)﹐非 F_VILLAGER NPC﹐不 include <weapon.h>。
// 持續性簡化：buff 以 add_temp("apply/...") 即時生效(戰鬥/技能即讀)﹐屬即時可驗版﹔
// 正式版應改為帶 call_out 倒數到期 delete_temp 的限時 buff。

#include <ansi.h>

inherit SKILL;

// 引源灸術參數(docs 只給定性﹐下為本次設計值)。
#define PT_SEN_COST     15      // 每次運針所耗的神(sen)現值。
#define PT_BUFF         20      // 強警/強動/強元素的加成量。
#define PT_FATIGUE_EASE 20      // fatigue 緩解量(削 fatigue 現值)。

// 引動的入門針招(無對手時的蓄勢氣象)。
mapping *actions = ({
  ([
    "action":		"$N指尖一引﹐$w如尋脈引泉﹐疾點$n的$l",
    "dodge":		0,
    "damage":		8,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N凝神引源﹐$w自死角探入$n的$l",
    "dodge":		-8,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N一式『引源歸經』﹐$w順勢扎向$n的$l",
    "dodge":		-5,
    "damage":		9,
    "damage_type":	"刺傷"
  ]),
});

string *interattack = ({
  "$N雙指夾針﹐針端隱隱牽動著一縷源氣﹐凝神辨認著$n身上的穴位。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("potency-needle");
  CHINESE_D->add_translate("potency-needle", "引源針法");
  setup();
}

void
attack_using (object me, object opponent, object weapon)
{
  int damage;

  if (!opponent)
    {
      if (me->query_temp("last_attacked_target"))
	message_vision (CYN + interattack[random(sizeof(interattack))] + NOR, me, weapon);
      return;
    }

  damage = COMBAT_D->fight(me, opponent, "potency-needle", actions[random(sizeof(actions))], weapon);
}

// 本針法可掛上 cauterization 灸術槽(enable cauterization with potency-needle)。
int
valid_enable (string usage)
{
  return usage == "cauterization";
}

// 強警/強動/強元素三者互斥的檢查：對同目標已掛任一﹐不得再掛另一。
private int has_exclusive (object t)
{
  return t->query_temp("potency/awareness")
      || t->query_temp("potency/move")
      || t->query_temp("potency/element");
}

// acupuncture <引源> to <目標>(簽名嚴格依 cmds/std/acupuncture.c)。
int
acupuncture_cauterization (object me, string func, object target)
{
  object t;
  int eased;

  if( !objectp(me) ) me = this_player();
  if( !objectp(me) ) return 0;

  t = target ? target : me;

  switch( func )
    {
    // —— fatigue 緩疲勞：削目標 fatigue 現值。 ——
    case "fatigue":
      if( me->query_stat("sen") < PT_SEN_COST )
        return notify_fail("你神識不足﹐運不起引源針法。\n");
      if( t->query_stat_maximum("fatigue") <= 0 || t->query_stat("fatigue") <= 0 )
        return notify_fail((t == me ? "你" : "對方")
          + "並不疲勞﹐毋須引源緩解。\n");

      me->consume_stat("sen", PT_SEN_COST, me);
      eased = t->consume_stat("fatigue", PT_FATIGUE_EASE, me);
      message_vision(GRN
        "$N持針引源﹐一式『紓疲引泉』緩緩點" + (t == me ? "自身" : "$N")
        + "百會、足三里諸穴﹐周身倦怠如潮水般退去。\n" NOR, me, t);
      tell_object(me, sprintf(HIW "(消 sen %d﹐%s疲勞 -%d)\n" NOR,
        PT_SEN_COST, t == me ? "自身" : "目標", eased));
      return 1;

    // —— awareness 強警：apply/awarness(engine 拼法)。 ——
    case "awareness":
      if( me->query_stat("sen") < PT_SEN_COST )
        return notify_fail("你神識不足﹐運不起引源針法。\n");
      if( has_exclusive(t) )
        return notify_fail("引源針法的強警、強動、強元素三者不可同時﹐"
          + (t == me ? "你" : "對方") + "身上已有一道源勁了。\n");

      me->consume_stat("sen", PT_SEN_COST, me);
      t->add_temp("apply/awarness", PT_BUFF);   // engine 鍵拼作 awarness。
      t->set_temp("potency/awareness", PT_BUFF);
      message_vision(HIC
        "$N運針引源﹐一式『靈台引明』疾點" + (t == me ? "自身" : "$N")
        + "靈台穴﹐六識為之一清﹐警敏大盛。\n" NOR, me, t);
      tell_object(me, sprintf(HIW "(消 sen %d﹐%s感應 +%d)\n" NOR,
        PT_SEN_COST, t == me ? "自身" : "目標", PT_BUFF));
      return 1;

    // —— move 強動：apply/move(行動力)。 ——
    case "move":
      if( me->query_stat("sen") < PT_SEN_COST )
        return notify_fail("你神識不足﹐運不起引源針法。\n");
      if( has_exclusive(t) )
        return notify_fail("引源針法的強警、強動、強元素三者不可同時﹐"
          + (t == me ? "你" : "對方") + "身上已有一道源勁了。\n");

      me->consume_stat("sen", PT_SEN_COST, me);
      t->add_temp("apply/move", PT_BUFF);
      t->set_temp("potency/move", PT_BUFF);
      message_vision(HIC
        "$N運針引源﹐一式『活絡引動』疾點" + (t == me ? "自身" : "$N")
        + "環跳、陽陵諸穴﹐周身關節一鬆﹐進退如風。\n" NOR, me, t);
      tell_object(me, sprintf(HIW "(消 sen %d﹐%s行動 +%d)\n" NOR,
        PT_SEN_COST, t == me ? "自身" : "目標", PT_BUFF));
      return 1;

    // —— element 強元素：apply/armor_vs_fire(元素抗性)。 ——
    case "element":
      if( me->query_stat("sen") < PT_SEN_COST )
        return notify_fail("你神識不足﹐運不起引源針法。\n");
      if( has_exclusive(t) )
        return notify_fail("引源針法的強警、強動、強元素三者不可同時﹐"
          + (t == me ? "你" : "對方") + "身上已有一道源勁了。\n");

      me->consume_stat("sen", PT_SEN_COST, me);
      t->add_temp("apply/armor_vs_fire", PT_BUFF);
      t->set_temp("potency/element", PT_BUFF);
      message_vision(HIR
        "$N運針引源﹐一式『罡源護元』疾點" + (t == me ? "自身" : "$N")
        + "命門、神闕諸穴﹐一層源氣護住周身﹐水火難侵。\n" NOR, me, t);
      tell_object(me, sprintf(HIW "(消 sen %d﹐%s元素抗性 +%d)\n" NOR,
        PT_SEN_COST, t == me ? "自身" : "目標", PT_BUFF));
      return 1;
    }

  return notify_fail("引源針法並無此引源之法。(可用﹕fatigue / awareness / "
    "move / element)\n");
}

// vim: set ts=4 sw=4 syntax=lpc
