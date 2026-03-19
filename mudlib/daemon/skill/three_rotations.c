// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N輕搖摺扇﹐$w順勢削向$n的$l",
    "dodge":		5,
    "damage":		5,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N踏乾坤步法﹐$w一轉斬向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N身形一旋﹐二轉之勢﹐一掌拍向$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N乾坤三轉﹐$w挾帶勁風劈向$n的$l",
    "dodge":		-15,
    "damage":		15,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N側身閃過﹐手肘順勢撞向$n的$l",
    "dodge":		10,
    "damage":		5,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N收扇為劍﹐$w點向$n的$l﹐劍意縱橫",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"割傷"
  ]),
});

string *interattack = ({
  "$N輕搖$n﹐神態從容﹐自有一股書生意氣。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("three rotations");
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

  damage = COMBAT_D->fight(me, opponent, "three rotations", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}
