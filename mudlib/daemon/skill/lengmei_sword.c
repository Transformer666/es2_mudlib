// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N手腕一翻﹐$w如寒梅吐蕊般刺向$n的$l",
    "dodge":		5,
    "damage":		5,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N身形一晃﹐$w帶著凜冽寒意斬向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N疾退一步﹐$w反手一劍削向$n的$l",
    "dodge":		10,
    "damage":		5,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N身形如電﹐$w化為一點寒芒直取$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N踏雪無痕般滑步上前﹐$w橫掃$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N冷然一笑﹐$w疾刺$n的$l﹐劍勢快如冰雪飄落",
    "dodge":		-15,
    "damage":		15,
    "damage_type":	"刺傷"
  ]),
});

string *interattack = ({
  "$N握著$n﹐神色冷峻﹐劍尖微微顫動。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("lengmei sword");
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

  damage = COMBAT_D->fight(me, opponent, "lengmei sword", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}
