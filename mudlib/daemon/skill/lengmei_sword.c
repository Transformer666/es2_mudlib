// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N使一招「寒梅傲雪」﹐$w如寒梅綻放般刺向$n的$l",
    "dodge":		-5,
    "damae":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N施展「冷月無聲」﹐$w悄然無息地斬向$n的$l",
    "dodge":		-10,
    "damage":		12,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N使出「梅花三弄」﹐$w連刺三劍取向$n的$l",
    "dodge":		5,
    "damae":		8,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N一招「暗香浮動」﹐$w帶著凜冽寒意削向$n的$l",
    "dodge":		10,
    "damage":		5,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N運起「疏影橫斜」﹐$w劍影橫斜掠過$n的$l",
    "dodge":		-15,
    "damae":		15,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N喝道「冰清玉潔」﹐$w化為一道冰寒劍氣射向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
});

string *interattack = ({
  "$N持劍在手﹐劍上彷彿散發出一股清冷的梅香。\n",
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

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("lengmei sword", 1);
    learn = me->query_learn("lengmei sword");

    if( !skill ) {
	if( learn >= 1500 ) {
	    tell_object(me,
		HIY "你感覺冷梅劍法的招式已經融會貫通﹗\n" NOR);
	    me->advance_skill("lengmei sword", 40);
	    me->gain_score("martial art", 500);
	}
	return;
    }

    if( (skill < 120) && (skill-39) * (skill-39) * 200 < learn - 1500 ) {
	me->advance_skill("lengmei sword", 1);
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
	tell_object(me, HIW "由於你冷梅劍法的修練有成﹐你的敏捷提高了。\n" NOR);
	me->add("dex", 1);
    }
}
