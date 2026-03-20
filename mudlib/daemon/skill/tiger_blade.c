// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N大喝一聲﹐$w如猛虎下山般劈向$n的$l",
    "dodge":		-10,
    "damage":		15,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N虎目圓睜﹐$w橫掃$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N低吼一聲﹐$w由下而上撩向$n的$l",
    "dodge":		5,
    "damage":		10,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N猛然前撲﹐$w挾帶虎威直砍$n的$l",
    "dodge":		-15,
    "damage":		15,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N一聲虎嘯﹐$w反手一刀削向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N身形暴起﹐$w凌空劈落$n的$l﹐勢如猛虎撲食",
    "dodge":		-10,
    "damage":		15,
    "damage_type":	"割傷"
  ]),
});

string *interattack = ({
  "$N緊握$n﹐虎目炯炯﹐殺氣騰騰。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("tiger blade");
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

  damage = COMBAT_D->fight(me, opponent, "tiger blade", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("tiger blade", 1);
    learn = me->query_learn("tiger blade");

    if( !skill ) {
	if( learn >= 1500 ) {
	    tell_object(me,
		HIY "你感覺虎刀的招式已經融會貫通﹗\n" NOR);
	    me->advance_skill("tiger blade", 40);
	    me->gain_score("martial art", 500);
	}
	return;
    }

    if( (skill < 120) && (skill-39) * (skill-39) * 200 < learn - 1500 ) {
	me->advance_skill("tiger blade", 1);
	me->gain_score("martial art", (skill+1) * 10);
	if( skill >= 50 )
	    me->gain_score("martial mastery", (skill-40) * 10);
    }
}

void skill_advanced(object me, string sk)
{
    int level;

    level = me->query_skill(sk, 1);
    if( level % 10 == 9 && me->query_attr("str") < level / 3 ) {
	tell_object(me, HIW "由於你虎刀的修練有成﹐你的膂力提高了。\n" NOR);
	me->add("str", 1);
    }
}
