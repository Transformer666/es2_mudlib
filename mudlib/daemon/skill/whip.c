// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N揚起$w朝$n的$l抽去",
    "dodge":		5,
    "damae":		5,
    "damage_type":	"鞭傷"
  ]),
  ([
    "action":		"$N手腕一抖﹐$w纏向$n的$l",
    "dodge":		-10,
    "damae":		10,
    "damage_type":	"鞭傷"
  ]),
  ([
    "action":		"$N猛然甩出$w﹐鞭梢劈向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"鞭傷"
  ]),
  ([
    "action":		"$N收回$w又猛然甩出﹐擊向$n的$l",
    "dodge":		10,
    "damae":		5,
    "damage_type":	"鞭傷"
  ]),
  ([
    "action":		"$N手中$w如蛇般纏向$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"鞭傷"
  ]),
  ([
    "action":		"$N一個旋身﹐$w捲向$n的$l",
    "dodge":		-5,
    "damae":		10,
    "damage_type":	"鞭傷"
  ]),
});

string *interattack = ({
  "$N揮舞著手中的$n﹐發出劈劈啪啪的響聲。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("whip");
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

  damage = COMBAT_D->fight(me, opponent, "whip", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}
