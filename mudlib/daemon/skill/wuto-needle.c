// 武陀灸術【五敗針法】 wuto-needle -- 武陀灸堂香主弟子的入門針法
//
// 這是一門針法(needle)技能﹐武陀灸堂一脈的根本針術。本檔比照龍圖丹派
// 的針法 daemon (amazing-needle.c) 的結構建立﹐使技能可被指派與習練。
// 基礎技能型別為 needle (針術)﹐見 feature/weapon/needle.c。中文字典已收
// 「武陀灸術【五敗針法】」一條(見 data/chinese.o)﹐故不需 add_translate。
//
// 灸術(cauterization)派發鏈(docs/03-門派與武功/07-方士-龍圖武陀.md L61、
// docs/02-遊戲系統與機制/06-煉丹與書本系統.md L100)：本針法可掛上 cauterization
// 灸術槽。玩家 `enable cauterization with wuto-needle` 後﹐
// `acupuncture fear to <目標>` 經 cmds/std/acupuncture.c 取 skill_mapped
// ("cauterization")(=「wuto-needle」)﹐呼
// SKILL_D("wuto-needle")->acupuncture_cauterization(me, "fear", target)。
//
// 五敗(docs L61：「fear/foul/fail/fling/fumble — 對應膽識/根骨/膂力/定力/機敏﹔
// 自身 delay 1﹐可能 delay 2 目標」)：對目標 debuff 一項屬性﹐並使施術者忙碌
// (start_busy delay 1)﹐有機率使目標亦忙碌(delay 2)。屬性對應(見 cmds/usr/score.c
// 與 daemon/skill/{dodge,parry,berserk}.c 註)：
//   fear   懼  -> 膽識 cor    foul  穢  -> 根骨 con    fail 弱 -> 膂力 str
//   fling  亂  -> 定力 cps    fumble 拙 -> 機敏 dex
//
// runtime 鐵則：不涉 ::die()/destruct()(#10)、不 replace_program(#11)﹔針法 daemon
// (inherit SKILL)﹐非 F_VILLAGER NPC﹐不 include <weapon.h>。
// 持續性簡化：debuff 以 add_temp("apply/<attr>", -N) 即時生效(query_attr 會疊加
// apply/﹐戰鬥即讀)﹔屬即時可驗版﹐正式版應改為帶 call_out 倒數回補的限時 debuff。

#include <ansi.h>

inherit SKILL;

// 五敗灸術參數(docs 只給定性﹐下為本次設計值)。
#define WT_SEN_COST     15      // 每下一敗針所耗的神(sen)現值。
#define WT_DEBUFF       3       // 對目標該屬性的削減量(apply/<attr> -= 此值)。
#define WT_SELF_DELAY   1       // docs：自身 delay 1(運針後忙碌一拍)。
#define WT_TARGET_DELAY 2       // docs：可能 delay 2 目標。
#define WT_TARGET_CHANCE 40     // 使目標亦 delay 的機率(%)。

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
    "action":		"$N欺身近前﹐一式『五敗截脈』連刺$n的$l",
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
    "action":		"$N一式『敗血封經』﹐$w自死角扎向$n的$l",
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
    "action":		"$N雙指夾針﹐一式『五敗摧心』連環點向$n的$l",
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
  DAEMON_D->register_skill_daemon("wuto-needle");
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

  damage = COMBAT_D->fight(me, opponent, "wuto-needle", actions[random(sizeof(actions))], weapon);
}

// 本針法可掛上 cauterization 灸術槽(enable cauterization with wuto-needle)。
int
valid_enable (string usage)
{
  return usage == "cauterization";
}

// 五敗 -> (屬性 key, 中文名, 針名)對照。
private mapping wuto_map = ([
  "fear"   : ({ "cor", "膽識", "懼敗針" }),
  "foul"   : ({ "con", "根骨", "穢敗針" }),
  "fail"   : ({ "str", "膂力", "弱敗針" }),
  "fling"  : ({ "cps", "定力", "亂敗針" }),
  "fumble" : ({ "dex", "機敏", "拙敗針" }),
]);

// acupuncture <五敗> to <目標>(簽名嚴格依 cmds/std/acupuncture.c：
// acupuncture_cauterization(object me, string func, object target))。
int
acupuncture_cauterization (object me, string func, object target)
{
  string attr, cname, nname;
  mixed *spec;

  if( !objectp(me) ) me = this_player();
  if( !objectp(me) ) return 0;

  if( undefinedp(spec = wuto_map[func]) )
    return notify_fail("五敗針法並無此敗。(可用﹕fear / foul / fail / "
      "fling / fumble)\n");

  if( !objectp(target) )
    return notify_fail("五敗針法須指定施敗的對象。(acupuncture "
      + func + " to <目標>)\n");

  if( target == me )
    return notify_fail("五敗針法乃損人之術﹐豈可自敗。\n");

  attr  = spec[0];
  cname = spec[1];
  nname = spec[2];

  if( me->query_stat("sen") < WT_SEN_COST )
    return notify_fail("你神識不足﹐運不起五敗針法。\n");

  me->consume_stat("sen", WT_SEN_COST, me);

  // 對目標削該屬性(apply/<attr> 為負﹐query_attr 會疊加)。
  target->add_temp("apply/" + attr, -WT_DEBUFF);

  message_vision(MAG
    "$N腕底藏針﹐一式『" + nname + "』疾點$n的要穴﹐"
    "一縷陰寒針勁順經竄入﹐$n只覺" + cname + "為之一挫。\n" NOR, me, target);
  tell_object(me, sprintf(HIW
    "(消 sen %d﹐目標 %s -%d)\n" NOR, WT_SEN_COST, cname, WT_DEBUFF));

  // 自身 delay 1(運針後忙碌一拍)。
  me->start_busy(WT_SELF_DELAY);

  // 可能 delay 2 目標。
  if( random(100) < WT_TARGET_CHANCE )
    {
      target->start_busy(WT_TARGET_DELAY);
      message_vision(MAG
        "$n穴道一麻﹐周身一滯﹐竟有片刻動彈不得﹗\n" NOR, me, target);
    }

  return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
