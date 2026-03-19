// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N舉起$w對準$n的$l劈了下去",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N將$w往$n的$l橫掃而出",
    "dodge":		-5,
    "damae":		5,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N揮動$w反手一刀斬向$n的$l",
    "dodge":		5,
    "damae":		10,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N低身前衝﹐手中$w朝$n的$l直削而去",
    "dodge":		-10,
    "damage":		15,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N大喝一聲﹐手中$w由下往上朝$n的$l撩去",
    "dodge":		-5,
    "damae":		5,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N微微側身﹐手中$w忽然朝$n$l砍出",
    "dodge":		5,
    "damage":		10,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N踏前一步﹐手中$w順勢往$n的$l斬去",
    "dodge":		-5,
    "damae":		10,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N將$w高高舉起﹐猛力朝$n的$l劈落",
    "dodge":		-15,
    "damage":		15,
    "damage_type":	"割傷"
  ]),
});

string *interattack = ({
  "$N握緊手中的$n﹐虎目圓睜盯著對手。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("blade");
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

  damage = COMBAT_D->fight(me, opponent, "blade", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}
