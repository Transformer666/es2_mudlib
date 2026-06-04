// 武陀灸術【驚異二針】 amazing-needle -- 武陀灸堂的入門針法
//
// 這是一門針法(needle)技能﹐武陀灸堂一脈的根本針術。本檔比照
// 武功招式 daemon (lunmay.c/blood_dagger.c) 的結構建立﹐使技能可被指派
// 與習練。基礎技能型別為 needle (針術)﹐見 feature/weapon/needle.c。
//
// 灸術(cauterization)派發鏈(docs/02-遊戲系統與機制/06-煉丹與書本系統.md L99、
// docs/03-門派與武功/07-方士-龍圖武陀.md L60)：本針法可掛上 cauterization 灸術槽
// (valid_enable("cauterization")=1)。玩家 `enable cauterization with amazing-needle`
// 後﹐`acupuncture amazing armor to <目標>` 經 cmds/std/acupuncture.c 取
// me->skill_mapped("cauterization")(此處 = "amazing-needle")﹐呼
// SKILL_D("amazing-needle")->acupuncture_cauterization(me, "amazing_armor", target)。
// 本檔以 acupuncture_cauterization 接灸術功能﹐與 attack_using 的戰鬥針招並存
// (additive，不影響原招式表)。
//
// 驚異二針三式(docs)：
//   amazing_armor 霸甲 -- 以「神(sen)」現值折為護甲﹐add_temp apply/armor。
//   amazing_power 霸氣 -- 以「神(sen)」現值折為傷害﹐add_temp apply/damage。
//   self_test     自試 -- 耗自身「氣(gin)」換取經驗(gain_score survive 軸)。
// docs 規則：霸甲/霸氣對同一目標不能同時(互斥)﹔對「自己」施術效果 4 倍。
//
// runtime 鐵則：本式不涉 ::die()/destruct()(#10)﹐亦不 replace_program(#11)﹔
// 為針法 daemon(inherit SKILL)﹐非 F_VILLAGER NPC﹐不 include <weapon.h>。
// 持續性簡化：buff 以 add_temp("apply/...") 即時生效(戰鬥即讀)﹐屬即時可驗版﹔
// 正式版應改為帶倒數(call_out 到期 delete_temp)的限時 buff。

#include <ansi.h>

inherit SKILL;

// 驚異二針灸術參數(docs 只給定性描述﹐下為本次設計值供日後平衡)。
#define AMZ_SEN_COST    20      // 霸甲/霸氣每次運針所耗的神(sen)現值。
#define AMZ_GIN_COST    30      // self_test 自試所耗的氣(gin)現值。
#define AMZ_SELF_MULT   4       // docs：對自己施術效果 4 倍。

mapping *actions = ({
  ([
    "action":		"$N手腕一沉﹐$w疾點$n的$l",
    "dodge":		5,
    "damage":		5,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N指尖一彈﹐$w如銀蛇吐信扎入$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N欺身近前﹐一式『驚異二針』連刺$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N凝神辨穴﹐$w精準地點向$n的$l",
    "dodge":		-15,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N手腕翻轉﹐$w詭異地繞向$n的$l",
    "dodge":		-10,
    "damage":		5,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N一式『封脈截經』﹐$w自死角扎向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N退步藏針﹐$w凝而後發疾刺$n的$l",
    "dodge":		10,
    "damage":		5,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N雙指夾針﹐一式『驚鴻照影』連環點向$n的$l",
    "dodge":		0,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
});

string *interattack = ({
  "$N雙指夾著$w﹐針尖微顫﹐凝神辨認著$n身上的穴位﹐靜待出手的時機。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("amazing-needle");
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

  damage = COMBAT_D->fight(me, opponent, "amazing-needle", actions[random(sizeof(actions))], weapon);
}

// 本針法可掛上 cauterization 灸術槽(enable cauterization with amazing-needle)﹐
// 比照 FORCE::valid_enable 回 usage=="force" 的模型。
int
valid_enable (string usage)
{
  return usage == "cauterization";
}

// acupuncture <灸術> to <目標> 的灸術派發終點(簽名嚴格依 cmds/std/acupuncture.c：
// acupuncture_cauterization(object me, string func, object target))。
// func 為去空白後的灸術名(amazing armor -> amazing_armor)。
int
acupuncture_cauterization (object me, string func, object target)
{
  object t;
  int sen_have, gin_have, bonus, mult, exp;

  if( !objectp(me) ) me = this_player();
  if( !objectp(me) ) return 0;

  switch( func )
    {
    // —— 霸甲 amazing_armor：神 → 護甲。對同目標與霸氣互斥。 ——
    case "amazing_armor":
      t = target ? target : me;
      mult = (t == me) ? AMZ_SELF_MULT : 1;

      if( t->query_temp("amazing/power") )
        return notify_fail(t == me
          ? "你身上的霸氣針勁未散﹐無法再下霸甲針。\n"
          : "對方身上的霸氣針勁未散﹐無法再下霸甲針。\n");

      sen_have = me->query_stat("sen");
      if( sen_have < AMZ_SEN_COST )
        return notify_fail("你神識不足﹐運不起驚異二針的霸甲之力。\n");

      me->consume_stat("sen", AMZ_SEN_COST, me);
      // 以施術後的神識現值折算護甲﹐對自己 4 倍。
      bonus = (me->query_stat("sen") / 4 + 5) * mult;
      t->add_temp("apply/armor", bonus);
      t->set_temp("amazing/armor", bonus);

      message_vision(HIC
        "$N凝神辨穴﹐一式『霸甲針』連點"
        + (t == me ? "自身" : "$N")
        + "周身大穴﹐護體真氣自針端勃發﹐結成一層無形鐵布衫。\n" NOR, me, t);
      tell_object(me, sprintf(HIW
        "(消 sen %d﹐%s護甲 +%d)\n" NOR, AMZ_SEN_COST,
        t == me ? "自身" : "目標", bonus));
      return 1;

    // —— 霸氣 amazing_power：神 → 傷害。對同目標與霸甲互斥。 ——
    case "amazing_power":
      t = target ? target : me;
      mult = (t == me) ? AMZ_SELF_MULT : 1;

      if( t->query_temp("amazing/armor") )
        return notify_fail(t == me
          ? "你身上的霸甲針勁未散﹐無法再下霸氣針。\n"
          : "對方身上的霸甲針勁未散﹐無法再下霸氣針。\n");

      sen_have = me->query_stat("sen");
      if( sen_have < AMZ_SEN_COST )
        return notify_fail("你神識不足﹐運不起驚異二針的霸氣之力。\n");

      me->consume_stat("sen", AMZ_SEN_COST, me);
      bonus = (me->query_stat("sen") / 4 + 5) * mult;
      t->add_temp("apply/damage", bonus);
      t->set_temp("amazing/power", bonus);

      message_vision(RED
        "$N指尖一震﹐一式『霸氣針』疾點"
        + (t == me ? "自身" : "$N")
        + "穴道﹐一股暴烈罡氣自針端注入經脈﹐殺氣陡盛。\n" NOR, me, t);
      tell_object(me, sprintf(HIW
        "(消 sen %d﹐%s傷害 +%d)\n" NOR, AMZ_SEN_COST,
        t == me ? "自身" : "目標", bonus));
      return 1;

    // —— self_test 自試：耗自身氣(gin)換取經驗(survive 軸即江湖歷練)。 ——
    case "self_test":
      gin_have = me->query_stat("gin");
      if( gin_have < AMZ_GIN_COST )
        return notify_fail("你氣力不足﹐沒辦法以驚異二針試針自勵。\n");

      me->consume_stat("gin", AMZ_GIN_COST, me);
      // 換得的經驗隨針法火候提高。
      exp = AMZ_GIN_COST + me->query_skill("amazing-needle", 1) / 2;
      if( exp < 1 ) exp = 1;
      me->gain_score("survive", exp);

      message_vision(YEL
        "$N深吸一口氣﹐持針自點周身要穴﹐以痛淬志、以針鍛骨﹐"
        "於苦試中體悟驚異二針的精微。\n" NOR, me);
      tell_object(me, sprintf(HIW
        "你以針自試﹐氣力大耗﹐卻頗有所悟。(消 gin %d﹐得歷練 %d)\n" NOR,
        AMZ_GIN_COST, exp));
      return 1;
    }

  return notify_fail("驚異二針並沒有這種灸法。(可用﹕amazing armor / "
    "amazing power / self test)\n");
}

// vim: set ts=4 sw=4 syntax=lpc
