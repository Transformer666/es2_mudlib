// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N一聲令下﹐指揮部下朝$n的$l發起攻擊",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N運籌帷幄﹐揮手示意部下包抄$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N大喝一聲﹐親自衝鋒朝$n的$l猛擊",
    "dodge":		-15,
    "damage":		15,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N以退為進﹐忽然反身一拳打向$n的$l",
    "dodge":		10,
    "damage":		5,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N厲聲喝令﹐部下如潮水般湧向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N擺出鶴翼陣勢﹐揮拳猛攻$n的$l",
    "dodge":		-10,
    "damage":		15,
    "damage_type":	"瘀傷"
  ]),
});

string *interattack = ({
  "$N目光銳利地觀察著戰場形勢﹐伺機而動。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("tactic");
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

  damage = COMBAT_D->fight(me, opponent, "tactic", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return usage == "command";
}
