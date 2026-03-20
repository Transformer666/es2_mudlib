// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N使一招「鬼影迷蹤」﹐$w忽隱忽現地斬向$n的$l",
    "dodge":		10,
    "damae":		5,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N施展「幻夢千重」﹐$w化作千道幻影削向$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N使出「虛實難辨」﹐$w虛虛實實刺向$n的$l",
    "dodge":		5,
    "damae":		8,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N一招「暗夜追魂」﹐$w如鬼魅般直取$n的$l",
    "dodge":		-15,
    "damage":		15,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N運起「飄渺劍影」﹐$w劍影飄渺掠過$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N喝道「夢魘纏身」﹐$w如噩夢般纏向$n的$l",
    "dodge":		-5,
    "damae":		12,
    "damage_type":	"割傷"
  ]),
});

string *interattack = ({
  "$N持劍在手﹐劍影幢幢﹐真假難辨。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("phantom sword");
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

  damage = COMBAT_D->fight(me, opponent, "phantom sword", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("phantom sword", 1);
    learn = me->query_learn("phantom sword");

    if( !skill ) {
	if( learn >= 1500 ) {
	    tell_object(me,
		HIY "你感覺幻影劍法的招式已經融會貫通﹗\n" NOR);
	    me->advance_skill("phantom sword", 40);
	    me->gain_score("martial art", 500);
	}
	return;
    }

    if( (skill < 120) && (skill-39) * (skill-39) * 200 < learn - 1500 ) {
	me->advance_skill("phantom sword", 1);
	me->gain_score("martial art", (skill+1) * 10);
	if( skill >= 50 )
	    me->gain_score("martial mastery", (skill-40) * 10);
    }
}

void skill_advanced(object me, string sk)
{
    int level;

    level = me->query_skill(sk, 1);
    if( level % 10 == 9 && me->query_attr("dex") < level / 3 ) {
	tell_object(me, HIW "由於你幻影劍法的修練有成﹐你的敏捷提高了。\n" NOR);
	me->add("dex", 1);
    }
}
