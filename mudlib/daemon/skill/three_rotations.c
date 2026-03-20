// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N輕搖摺扇﹐$w順勢削向$n的$l",
    "dodge":		5,
    "damage":		5,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N踏乾坤步法﹐$w一轉斬向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N身形一旋﹐二轉之勢﹐一掌拍向$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N乾坤三轉﹐$w挾帶勁風劈向$n的$l",
    "dodge":		-15,
    "damage":		15,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N側身閃過﹐手肘順勢撞向$n的$l",
    "dodge":		10,
    "damage":		5,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N收扇為劍﹐$w點向$n的$l﹐劍意縱橫",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"割傷"
  ]),
});

string *interattack = ({
  "$N輕搖$n﹐神態從容﹐自有一股書生意氣。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("three rotations");
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

  damage = COMBAT_D->fight(me, opponent, "three rotations", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("three rotations", 1);
    learn = me->query_learn("three rotations");

    if( !skill ) {
	if( learn >= 1500 ) {
	    tell_object(me,
		HIY "你感覺三轉劍法的招式已經融會貫通﹗\n" NOR);
	    me->advance_skill("three rotations", 40);
	    me->gain_score("martial art", 500);
	}
	return;
    }

    if( (skill < 120) && (skill-39) * (skill-39) * 200 < learn - 1500 ) {
	me->advance_skill("three rotations", 1);
	me->gain_score("martial art", (skill+1) * 10);
	if( skill >= 50 )
	    me->gain_score("martial mastery", (skill-40) * 10);
    }
}

void skill_advanced(object me, string sk)
{
    int level;

    level = me->query_skill(sk, 1);
    if( level % 10 == 9 && me->query_attr("int") < level / 3 ) {
	tell_object(me, HIW "由於你三轉劍法的修練有成﹐你的悟性提高了。\n" NOR);
	me->add("int", 1);
    }
}
