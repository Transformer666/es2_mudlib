// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N手中$w一抖﹐劍尖直刺$n的$l",
    "dodge":		5,
    "damage":		5,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N踏前一步﹐$w化作一道寒光斬向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N縱身躍起﹐$w挾著風聲朝$n的$l劈落",
    "dodge":		-10,
    "damage":		15,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N側身閃過﹐$w順勢削向$n的$l",
    "dodge":		10,
    "damage":		5,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N沉腰坐馬﹐$w穩穩刺向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N長嘯一聲﹐手中$w如封山絕壁般橫掃$n的$l",
    "dodge":		-15,
    "damage":		15,
    "damage_type":	"割傷"
  ]),
});

string *interattack = ({
  "$N持$n在手﹐劍勢如山嶽般沉穩。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("fengshan sword");
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

  damage = COMBAT_D->fight(me, opponent, "fengshan sword", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}
