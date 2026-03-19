// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N持$w往$n的$l直刺而去",
    "dodge":		5,
    "damae":		5,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N將$w一抖﹐槍頭刺向$n的$l",
    "dodge":		-5,
    "damae":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N舞動$w﹐朝$n的$l橫掃而去",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N踏前一步﹐$w如蛇般刺向$n的$l",
    "dodge":		-10,
    "damae":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N收槍回身﹐猛然刺出$w直取$n的$l",
    "dodge":		10,
    "damage":		15,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N一個箭步上前﹐$w橫掃$n的$l",
    "dodge":		-5,
    "damae":		5,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N低身下蹲﹐$w如游龍般直取$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
});

string *interattack = ({
  "$N持$n在手﹐槍尖微微顫動。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("pike");
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

  damage = COMBAT_D->fight(me, opponent, "pike", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}
