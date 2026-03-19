// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N大喝一聲﹐$w如猛虎下山般劈向$n的$l",
    "dodge":		-10,
    "damage":		15,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N虎目圓睜﹐$w橫掃$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N低吼一聲﹐$w由下而上撩向$n的$l",
    "dodge":		5,
    "damage":		10,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N猛然前撲﹐$w挾帶虎威直砍$n的$l",
    "dodge":		-15,
    "damage":		15,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N一聲虎嘯﹐$w反手一刀削向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N身形暴起﹐$w凌空劈落$n的$l﹐勢如猛虎撲食",
    "dodge":		-10,
    "damage":		15,
    "damage_type":	"割傷"
  ]),
});

string *interattack = ({
  "$N緊握$n﹐虎目炯炯﹐殺氣騰騰。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("tiger blade");
  setup();
}

void
attack_using (object me, object opponent, object weapon)
{
  int damage;

  if (!opponent)
    {
      if (me->query_temp("last_attacked_target"))
	message_vision (CYN + interattack[random(sizeof(interattack))] + NOR,me, weapon);
      return;
    }

  damage = COMBAT_D->fight(me, opponent, "tiger blade", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}
