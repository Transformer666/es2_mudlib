// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N蹲低身子﹐手中$w刺向$n的$l",
    "dodge":		5,
    "damae":		5,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N揮動$w，往$n的$l斬下",
    "dodge":		-5,
    "damae":		10,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N高舉$w，往前一跳斬向$n的$l",
    "dodge":		-10,
    "damae":		10,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N將手中$w舉在胸前﹐衝出幾部對準$n的$l刺出一劍",
    "dodge":		-15,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N側過身子﹐手中$w對準$n的$l斜斜刺出",
    "dodge":		-10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N一個轉身手中的$w忽然揮出﹐斬向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N退後一步，手中$w對準$n$l一劍刺去",
    "dodge":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N微微矮身﹐向前躍出一步同時$w斬向$n的$l",
    "damage":		10,
    "damage_type":	"割傷"
  ]),
});

string *interattack = ({
  "$N緊握著手中的$n﹐緩緩移動。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("sword");
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

  damage = COMBAT_D->fight(me, opponent, "sword", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("sword", 1);
    learn = me->query_learn("sword");

    if( !skill ) {
	if( learn >= 500 ) {
	    tell_object(me,
		HIY "你覺得自己的劍法已有所領悟﹗\n" NOR);
	    me->advance_skill("sword", 1);
	}
	return;
    }

    if( (skill < 120) && (skill) * (skill) * 100 < learn - 500 ) {
	me->advance_skill("sword", 1);
	me->gain_score("martial art", (skill+1) * 5);
    }
}

void skill_advanced(object me, string sk)
{
    int level;

    level = me->query_skill(sk, 1);
    if( level % 10 == 9 && me->query_attr("dex") < level / 4 ) {
	tell_object(me, HIW "由於你勤練劍法﹐你的敏捷提高了。\n" NOR);
	me->add("dex", 1);
    }
}

