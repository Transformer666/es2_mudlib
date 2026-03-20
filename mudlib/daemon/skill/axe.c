// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N掄起$w朝$n的$l猛劈過去",
    "dodge":		-15,
    "damage":		15,
    "damage_type":	"砍傷"
  ]),
  ([
    "action":		"$N舉起$w由上往下朝$n的$l砍去",
    "dodge":		-10,
    "damae":		10,
    "damage_type":	"砍傷"
  ]),
  ([
    "action":		"$N大吼一聲﹐手中$w橫掃$n的$l",
    "dodge":		-5,
    "damae":		10,
    "damage_type":	"砍傷"
  ]),
  ([
    "action":		"$N側身一轉﹐$w順勢朝$n的$l劈出",
    "dodge":		5,
    "damage":		10,
    "damage_type":	"砍傷"
  ]),
  ([
    "action":		"$N雙手持$w用力朝$n的$l劈落",
    "dodge":		-15,
    "damage":		20,
    "damage_type":	"砍傷"
  ]),
  ([
    "action":		"$N低喝一聲﹐$w由下朝$n的$l撩起",
    "dodge":		-10,
    "damae":		5,
    "damage_type":	"砍傷"
  ]),
});

string *interattack = ({
  "$N將$n扛在肩上﹐冷冷地盯著敵人。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("axe");
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

  damage = COMBAT_D->fight(me, opponent, "axe", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("axe", 1);
    learn = me->query_learn("axe");

    if( !skill ) {
	if( learn >= 500 ) {
	    tell_object(me,
		HIY "你覺得自己的斧法已有所領悟﹗\n" NOR);
	    me->advance_skill("axe", 1);
	}
	return;
    }

    if( (skill < 120) && (skill) * (skill) * 100 < learn - 500 ) {
	me->advance_skill("axe", 1);
	me->gain_score("martial art", (skill+1) * 5);
    }
}

void skill_advanced(object me, string sk)
{
    int level;

    level = me->query_skill(sk, 1);
    if( level % 10 == 9 && me->query_attr("str") < level / 4 ) {
	tell_object(me, HIW "由於你勤練斧法﹐你的膂力提高了。\n" NOR);
	me->add("str", 1);
    }
}
