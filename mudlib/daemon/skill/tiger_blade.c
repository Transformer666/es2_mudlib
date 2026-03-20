// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N使一招「猛虎下山」﹐手中$w猛然劈向$n的$l",
    "dodge":		-10,
    "damae":		10,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N大喝一聲﹐一式「虎嘯山林」﹐$w橫掃$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"斲傷"
  ]),
  ([
    "action":		"$N低身前撲﹐「白虎撲食」﹐$w直取$n的$l",
    "dodge":		-15,
    "damage":		15,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N猛然轉身﹐一招「猛虎擺尾」﹐$w反掃$n的$l",
    "dodge":		5,
    "damae":		8,
    "damage_type":	"斲傷"
  ]),
  ([
    "action":		"$N虎目圓睜﹐使出「虎牙劈空」﹐$w凌空劈向$n的$l",
    "dodge":		-10,
    "damae":		12,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N氣沉丹田﹐「卧虎藏鋒」一刀突襲$n的$l",
    "dodge":		10,
    "damage":		5,
    "damage_type":	"割傷"
  ]),
});

string *interattack = ({
  "$N手持虎刀﹐殺氣如猛虎般凶猛。\n",
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
