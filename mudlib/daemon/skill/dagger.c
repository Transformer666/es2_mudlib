// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N持$w往$n的$l刺去",
    "dodge":		5,
    "damae":		5,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N閃身上前﹐$w朝$n的$l劃去",
    "dodge":		-5,
    "damae":		5,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N欺身而進﹐$w直刺$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N反手持$w﹐朝$n的$l抹去",
    "dodge":		5,
    "damae":		5,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N忽然暴起﹐$w朝$n的$l猛刺",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N一個側身﹐$w劃向$n的$l",
    "dodge":		10,
    "damae":		5,
    "damage_type":	"割傷"
  ]),
});

string *interattack = ({
  "$N將$n反握在手中﹐身子微微前傾。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("dagger");
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

  damage = COMBAT_D->fight(me, opponent, "dagger", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}
