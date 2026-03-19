// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N指尖一彈﹐$w如毒蛇吐信般射向$n的$l穴道",
    "dodge":		5,
    "damage":		5,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N手腕翻轉﹐$w連珠疾射取$n的$l要穴",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N凝神瞄準﹐$w無聲無息地刺向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N虛晃一招﹐$w暗中取$n的$l死穴",
    "dodge":		10,
    "damage":		5,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N三指齊發﹐$w如三星連珠射向$n的$l",
    "dodge":		-15,
    "damage":		15,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N身形一閃﹐$w已自近身刺入$n的$l穴位",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
});

string *interattack = ({
  "$N指間夾著$n﹐目光如炬地注視著對手。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("five defeat needle");
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

  damage = COMBAT_D->fight(me, opponent, "five defeat needle", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}
