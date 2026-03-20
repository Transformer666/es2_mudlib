// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N揮動$w朝$n的$l橫掃而去",
    "dodge":		-5,
    "damae":		5,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N舉起$w往$n的$l砸了下去",
    "dodge":		-10,
    "damae":		10,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N抬起$w朝$n的$l猛戳過去",
    "dodge":		5,
    "damae":		5,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N旋轉$w﹐一端朝$n的$l搗去",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N倒轉$w﹐朝$n的$l用力一擊",
    "dodge":		10,
    "damage":		10,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N一個轉身﹐$w橫掃$n的$l",
    "dodge":		-10,
    "damae":		10,
    "damage_type":	"瘀傷"
  ]),
});

string *interattack = ({
  "$N持$n在手﹐穩穩地站定。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("staff");
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

  damage = COMBAT_D->fight(me, opponent, "staff", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("staff", 1);
    learn = me->query_learn("staff");

    if( !skill ) {
	if( learn >= 500 ) {
	    tell_object(me,
		HIY "你覺得自己的棍法已有所領悟﹗\n" NOR);
	    me->advance_skill("staff", 1);
	}
	return;
    }

    if( (skill < 120) && (skill) * (skill) * 100 < learn - 500 ) {
	me->advance_skill("staff", 1);
	me->gain_score("martial art", (skill+1) * 5);
    }
}

void skill_advanced(object me, string sk)
{
    int level;

    level = me->query_skill(sk, 1);
    if( level % 10 == 9 && me->query_attr("str") < level / 4 ) {
	tell_object(me, HIW "由於你勤練棍法﹐你的膂力提高了。\n" NOR);
	me->add("str", 1);
    }
}
