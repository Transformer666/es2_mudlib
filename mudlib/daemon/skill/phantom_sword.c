// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N手中$w忽隱忽現﹐幻影般斬向$n的$l",
    "dodge":		10,
    "damage":		5,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N身形虛晃﹐$w化作數道幻影同時削向$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N一劍刺出﹐$w劍影重重﹐虛虛實實取向$n的$l",
    "dodge":		5,
    "damage":		10,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N倏然消失在原處﹐$w已自虛空中斬向$n的$l",
    "dodge":		-15,
    "damage":		15,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N手腕顫動﹐$w幻化出漫天劍花罩向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N輕喝一聲﹐$w如夢似幻地掠過$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"割傷"
  ]),
});

string *interattack = ({
  "$N持$n在手﹐身形飄忽不定﹐如幻似真。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("phantom sword");
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

  damage = COMBAT_D->fight(me, opponent, "phantom sword", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}
