// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N使一招「峰回路轉」﹐手中$w一抖﹐劍尖直刺$n的$l",
    "dodge":		5,
    "damage":		5,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N一式「空山鳥語」﹐$w化作一道寒光斬向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N一招「御風而行」﹐縱身躍起﹐$w挾著風聲朝$n的$l劈落",
    "dodge":		-10,
    "damage":		15,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N使出「旭日東升」﹐側身閃過﹐$w順勢削向$n的$l",
    "dodge":		10,
    "damage":		5,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N一式「金光瀉地」﹐沉腰坐馬﹐$w穩穩刺向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N長嘯一聲﹐使出「空谷秋虹」﹐$w如封山絕壁般橫掃$n的$l",
    "dodge":		-15,
    "damage":		15,
    "damage_type":	"割傷"
  ]),
});

string *interattack = ({
  "$N持$n在手﹐劍勢如山嶽般沉穩。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("fengshan sword");
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

  damage = COMBAT_D->fight(me, opponent, "fengshan sword", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("fengshan sword", 1);
    learn = me->query_learn("fengshan sword");

    if( !skill ) {
	if( learn >= 1500 ) {
	    tell_object(me,
		HIY "你感覺封山劍法的招式已經融會貫通﹗\n" NOR);
	    me->advance_skill("fengshan sword", 40);
	    me->gain_score("martial art", 500);
	}
	return;
    }

    if( (skill < 120) && (skill-39) * (skill-39) * 200 < learn - 1500 ) {
	me->advance_skill("fengshan sword", 1);
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
	tell_object(me, HIW "由於你封山劍法的修練有成﹐你的敏捷提高了。\n" NOR);
	me->add("dex", 1);
    }
}
