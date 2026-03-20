// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N揚起$w朝$n的$l抽去",
    "dodge":		5,
    "damae":		5,
    "damage_type":	"鞭傷"
  ]),
  ([
    "action":		"$N手腕一抖﹐$w纏向$n的$l",
    "dodge":		-10,
    "damae":		10,
    "damage_type":	"鞭傷"
  ]),
  ([
    "action":		"$N猛然甩出$w﹐鞭梢劈向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"鞭傷"
  ]),
  ([
    "action":		"$N收回$w又猛然甩出﹐擊向$n的$l",
    "dodge":		10,
    "damae":		5,
    "damage_type":	"鞭傷"
  ]),
  ([
    "action":		"$N手中$w如蛇般纏向$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"鞭傷"
  ]),
  ([
    "action":		"$N一個旋身﹐$w捲向$n的$l",
    "dodge":		-5,
    "damae":		10,
    "damage_type":	"鞭傷"
  ]),
});

string *interattack = ({
  "$N揮舞著手中的$n﹐發出劈劈啪啪的響聲。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("whip");
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

  damage = COMBAT_D->fight(me, opponent, "whip", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("whip", 1);
    learn = me->query_learn("whip");

    if( !skill ) {
	if( learn >= 500 ) {
	    tell_object(me,
		HIY "你覺得自己的鞭法已有所領悟﹗\n" NOR);
	    me->advance_skill("whip", 1);
	}
	return;
    }

    if( (skill < 120) && (skill) * (skill) * 100 < learn - 500 ) {
	me->advance_skill("whip", 1);
	me->gain_score("martial art", (skill+1) * 5);
    }
}

void skill_advanced(object me, string sk)
{
    int level;

    level = me->query_skill(sk, 1);
    if( level % 10 == 9 && me->query_attr("dex") < level / 4 ) {
	tell_object(me, HIW "由於你勤練鞭法﹐你的敏捷提高了。\n" NOR);
	me->add("dex", 1);
    }
}
