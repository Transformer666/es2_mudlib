// 小步玄劍 buxuan-sword -- 步玄派居士的入門劍法
//
// 步玄派書生一脈以劍法佐控場﹐這套小步玄劍乃居士入門的根本劍術﹐
// 講究身隨步轉、劍走輕靈﹐配合步玄七絕(myst-steps)的身法施展。本檔
// 比照 sword.c/lunmay.c 的結構建立﹐使技能可被指派與習練。
// TODO: combat specifics -- 與步法(myst-steps)、內功(myst-force)聯動的
//       控場/減速效果﹐及進階招式判定。

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N腳踏玄步﹐$w斜斜一引刺向$n的$l",
    "dodge":		5,
    "damage":		5,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N身形一轉﹐$w化作一道青芒掠向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N一式『乾坤初轉』﹐$w盤旋而出撩向$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N步隨劍走﹐手中$w如行雲流水直點$n的$l",
    "dodge":		-15,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N側身遊走﹐$w斜挑而上劃向$n的$l",
    "dodge":		-10,
    "damage":		5,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N一招『玄機暗藏』﹐$w忽地繞向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N退步蓄勢﹐$w凝而後發直刺$n的$l",
    "dodge":		10,
    "damage":		5,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N足尖輕點﹐一式『步玄歸元』連環斬向$n的$l",
    "dodge":		0,
    "damage":		10,
    "damage_type":	"割傷"
  ]),
});

string *interattack = ({
  "$N長劍斜引﹐步法暗轉﹐宛如閒庭信步﹐靜待出手的時機。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("buxuan-sword");
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

  damage = COMBAT_D->fight(me, opponent, "buxuan-sword", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
