// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N口誦咒語﹐$w燃起火焰斬向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"灼傷"
  ]),
  ([
    "action":		"$N掐訣念咒﹐$w凝聚寒霜劈向$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N踏罡布雷﹐$w帶著雷電之威刺向$n的$l",
    "dodge":		-15,
    "damage":		15,
    "damage_type":	"灼傷"
  ]),
  ([
    "action":		"$N御風而動﹐$w乘風勢削向$n的$l",
    "dodge":		5,
    "damage":		5,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N以指引劍﹐$w赤焰纏繞斬向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"灼傷"
  ]),
  ([
    "action":		"$N低喝一聲﹐$w化作一道寒冰劍氣射向$n的$l",
    "dodge":		-10,
    "damage":		15,
    "damage_type":	"割傷"
  ]),
});

string *interattack = ({
  "$N持$n在手﹐劍身隱隱發出奇異的光芒。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("maoshan sword");
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

  damage = COMBAT_D->fight(me, opponent, "maoshan sword", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("maoshan sword", 1);
    learn = me->query_learn("maoshan sword");

    if( !skill ) {
	if( learn >= 1500 ) {
	    tell_object(me,
		HIY "你感覺茅山劍法的招式已經融會貫通﹗\n" NOR);
	    me->advance_skill("maoshan sword", 40);
	    me->gain_score("martial art", 500);
	}
	return;
    }

    if( (skill < 120) && (skill-39) * (skill-39) * 200 < learn - 1500 ) {
	me->advance_skill("maoshan sword", 1);
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
	tell_object(me, HIW "由於你茅山劍法的修練有成﹐你的敏捷提高了。\n" NOR);
	me->add("dex", 1);
    }
}
