// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N舉起$w﹐大喝一聲朝$n的$l猛力砸下",
    "dodge":		-10,
    "damage":		15,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N橫掃$w﹐沉重的鎚身掃向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N踏前一步﹐$w如金剛降魔般搗向$n的$l",
    "dodge":		-15,
    "damage":		15,
    "damage_type":	"砍傷"
  ]),
  ([
    "action":		"$N旋轉$w﹐借著旋轉之力砸向$n的$l",
    "dodge":		5,
    "damage":		10,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N口宣佛號﹐$w由上而下劈向$n的$l",
    "dodge":		-10,
    "damage":		15,
    "damage_type":	"砍傷"
  ]),
  ([
    "action":		"$N低喝一聲﹐$w直搗$n的$l﹐勢若千鈞",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"瘀傷"
  ]),
});

string *interattack = ({
  "$N雙手持$n﹐穩如泰山﹐一身金剛之氣。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("diamond hammer");
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

  damage = COMBAT_D->fight(me, opponent, "diamond hammer", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}
