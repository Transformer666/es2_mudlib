// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N使一招「太乙真火」﹐$w燃起真火斬向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N施展「紫微星落」﹐$w化作一道星光刺向$n的$l",
    "dodge":		-10,
    "damae":		12,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N使出「北斗七殺」﹐$w連環七劍劈向$n的$l",
    "dodge":		-15,
    "damage":		15,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N運起「天罡正氣」﹐$w挾帶浩然正氣削向$n的$l",
    "dodge":		5,
    "damae":		8,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N一招「玄天破魔」﹐$w劍氣凜然直取$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N喝道「星河倒轉」﹐$w旋轉如星河般掃向$n的$l",
    "dodge":		10,
    "damae":		5,
    "damage_type":	"割傷"
  ]),
});

string *interattack = ({
  "$N持劍在手﹐太乙劍法隱隱透出一股凜然正氣。\n",
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

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("taiyi sword", 1);
    learn = me->query_learn("taiyi sword");

    if( !skill ) {
	if( learn >= 1500 ) {
	    tell_object(me,
		HIY "你感覺太乙劍法的招式已經融會貫通﹗\n" NOR);
	    me->advance_skill("taiyi sword", 40);
	    me->gain_score("martial art", 500);
	}
	return;
    }

    if( (skill < 120) && (skill-39) * (skill-39) * 200 < learn - 1500 ) {
	me->advance_skill("taiyi sword", 1);
	me->gain_score("martial art", (skill+1) * 10);
	if( skill >= 50 )
	    me->gain_score("martial mastery", (skill-40) * 10);
    }
}

void skill_advanced(object me, string sk)
{
    int level;

    level = me->query_skill(sk, 1);
    if( level % 10 == 9 && me->query_attr("spi") < level / 3 ) {
	tell_object(me, HIW "由於你太乙劍法的修練有成﹐你的靈性提高了。\n" NOR);
	me->add("spi", 1);
    }
}
