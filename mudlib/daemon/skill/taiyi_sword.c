// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N輕揮$w﹐劍走太極圓弧斬向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N身隨劍轉﹐$w順勢刺向$n的$l",
    "dodge":		5,
    "damage":		5,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N踏罡步斗﹐$w帶著道韻直取$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N御劍凌風﹐$w化為一道清光劈向$n的$l",
    "dodge":		-15,
    "damage":		15,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N氣沉丹田﹐$w以柔勁削向$n的$l",
    "dodge":		10,
    "damage":		5,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N旋身一轉﹐$w畫出一道太乙劍圈掃向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"割傷"
  ]),
});

string *interattack = ({
  "$N持$n在手﹐劍意綿綿﹐自有一股道家風範。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("taiyi sword");
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

  damage = COMBAT_D->fight(me, opponent, "taiyi sword", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}
