// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N持$w往$n的$l刺去",
    "dodge":		5,
    "damae":		5,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N閃身上前﹐$w朝$n的$l劃去",
    "dodge":		-5,
    "damae":		5,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N欺身而進﹐$w直刺$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N反手持$w﹐朝$n的$l抹去",
    "dodge":		5,
    "damae":		5,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N忽然暴起﹐$w朝$n的$l猛刺",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N一個側身﹐$w劃向$n的$l",
    "dodge":		10,
    "damae":		5,
    "damage_type":	"割傷"
  ]),
});

string *interattack = ({
  "$N將$n反握在手中﹐身子微微前傾。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("dagger");
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

  damage = COMBAT_D->fight(me, opponent, "dagger", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("dagger", 1);
    learn = me->query_learn("dagger");

    if( !skill ) {
	if( learn >= 500 ) {
	    tell_object(me,
		HIY "你覺得自己的匕首技巧已有所領悟﹗\n" NOR);
	    me->advance_skill("dagger", 1);
	}
	return;
    }

    if( (skill < 120) && (skill) * (skill) * 100 < learn - 500 ) {
	me->advance_skill("dagger", 1);
	me->gain_score("martial art", (skill+1) * 5);
    }
}

void skill_advanced(object me, string sk)
{
    int level;

    level = me->query_skill(sk, 1);
    if( level % 10 == 9 && me->query_attr("dex") < level / 4 ) {
	tell_object(me, HIW "由於你勤練匕首﹐你的敏捷提高了。\n" NOR);
	me->add("dex", 1);
    }
}
