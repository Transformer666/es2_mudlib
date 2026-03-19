// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N揮動$w朝$n的$l橫掃而去",
    "dodge":		-5,
    "damae":		5,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N舉起$w往$n的$l砸了下去",
    "dodge":		-10,
    "damae":		10,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N抬起$w朝$n的$l猛戳過去",
    "dodge":		5,
    "damae":		5,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N旋轉$w﹐一端朝$n的$l搗去",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N倒轉$w﹐朝$n的$l用力一擊",
    "dodge":		10,
    "damage":		10,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N一個轉身﹐$w橫掃$n的$l",
    "dodge":		-10,
    "damae":		10,
    "damage_type":	"瘀傷"
  ]),
});

string *interattack = ({
  "$N持$n在手﹐穩穩地站定。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("staff");
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

  damage = COMBAT_D->fight(me, opponent, "staff", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}
