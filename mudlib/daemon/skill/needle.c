// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N手腕一翻﹐$w刺向$n的$l",
    "dodge":		10,
    "damae":		5,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N探出$w﹐直取$n的$l",
    "dodge":		-5,
    "damae":		5,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N一個閃身﹐$w點向$n的$l",
    "dodge":		5,
    "damage":		5,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N手中$w連環刺出﹐攻向$n的$l",
    "dodge":		-10,
    "damae":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N低身前撲﹐$w直取$n的$l要害",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N虛晃一招﹐$w忽然點向$n的$l",
    "dodge":		10,
    "damae":		5,
    "damage_type":	"刺傷"
  ]),
});

string *interattack = ({
  "$N將$n握在掌心﹐凝神注視著對手。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("needle");
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

  damage = COMBAT_D->fight(me, opponent, "needle", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("needle", 1);
    learn = me->query_learn("needle");

    if( !skill ) {
	if( learn >= 500 ) {
	    tell_object(me,
		HIY "你覺得自己的針法已有所領悟﹗\n" NOR);
	    me->advance_skill("needle", 1);
	}
	return;
    }

    if( (skill < 120) && (skill) * (skill) * 100 < learn - 500 ) {
	me->advance_skill("needle", 1);
	me->gain_score("martial art", (skill+1) * 5);
    }
}

void skill_advanced(object me, string sk)
{
    int level;

    level = me->query_skill(sk, 1);
    if( level % 10 == 9 && me->query_attr("dex") < level / 4 ) {
	tell_object(me, HIW "由於你勤練針法﹐你的敏捷提高了。\n" NOR);
	me->add("dex", 1);
    }
}
