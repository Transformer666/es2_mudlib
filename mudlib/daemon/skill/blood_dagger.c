// 血魂匕法【赤】 blood dagger -- 瑯夷派黑龍左使的入門匕法
//
// 這是一門匕法(dagger)技能﹐瑯夷派黑龍左使一脈的根本殺招。本檔比照
// 武功招式 daemon (lunmay.c/sword.c) 的結構建立﹐使技能可被指派與習練。
// 基礎技能型別為 dagger (錐法)﹐見 feature/weapon/dagger.c。
// TODO: combat specifics -- 暗算/背刺加成、見血追擊、精/警覺消耗等機制。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N壓低身形﹐手中$w自下而上挑向$n的$l",
    "dodge":		5,
    "damage":		5,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N腕底一抖﹐$w如毒蛇吐信疾刺$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N欺身近前﹐一式『血濺三尺』割向$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N足尖一錯﹐$w貼著$n的$l斜斜抹過",
    "dodge":		-15,
    "damage":		10,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N手腕翻轉﹐$w詭異地繞向$n的$l",
    "dodge":		-10,
    "damage":		5,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N一招『赤魂索命』﹐$w自死角刺向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N退步藏鋒﹐$w凝而後發疾撩$n的$l",
    "dodge":		10,
    "damage":		5,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N身形一矮﹐反手一式『黑龍纏絲』刺入$n的$l",
    "dodge":		0,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
});

string *interattack = ({
  "$N反手握著$n﹐刃光內斂﹐如毒蛇蟄伏﹐靜待噬人的時機。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("blood dagger");
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

  damage = COMBAT_D->fight(me, opponent, "blood dagger", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
