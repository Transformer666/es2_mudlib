// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N出手如電﹐$w瞬間刺入$n的$l經脈",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N雙指一彈﹐$w帶著驚人勁力射向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N身法詭異地閃到$n身側﹐$w直取$n的$l命穴",
    "dodge":		5,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N冷笑一聲﹐$w劃出驚異弧線刺向$n的$l",
    "dodge":		-15,
    "damage":		15,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N手中$w忽然化為兩道銀光﹐同時射向$n的$l",
    "dodge":		-10,
    "damage":		15,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N虛實難辨地一晃﹐$w已然沒入$n的$l穴道",
    "dodge":		10,
    "damage":		5,
    "damage_type":	"刺傷"
  ]),
});

string *interattack = ({
  "$N指間$n閃爍寒光﹐令人不寒而慄。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("amazing needle");
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

  damage = COMBAT_D->fight(me, opponent, "amazing needle", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}
