// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N舉起$w朝$n的$l猛砸下去",
    "dodge":		-10,
    "damae":		10,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N揮動$w橫掃$n的$l",
    "dodge":		-5,
    "damae":		5,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N大喝一聲﹐$w由上而下砸向$n的$l",
    "dodge":		-15,
    "damage":		15,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N踏前一步﹐$w直搗$n的$l",
    "dodge":		5,
    "damae":		5,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N一個轉身﹐$w重重敲向$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N雙手握鎚﹐$w猛力搗向$n的$l",
    "dodge":		-5,
    "damage":		10,
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
  DAEMON_D->register_skill_daemon("hammer");
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

  damage = COMBAT_D->fight(me, opponent, "hammer", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("hammer", 1);
    learn = me->query_learn("hammer");

    if( !skill ) {
	if( learn >= 500 ) {
	    tell_object(me,
		HIY "你覺得自己的鎚法已有所領悟﹗\n" NOR);
	    me->advance_skill("hammer", 1);
	}
	return;
    }

    if( (skill < 120) && (skill) * (skill) * 100 < learn - 500 ) {
	me->advance_skill("hammer", 1);
	me->gain_score("martial art", (skill+1) * 5);
    }
}

void skill_advanced(object me, string sk)
{
    int level;

    level = me->query_skill(sk, 1);
    if( level % 10 == 9 && me->query_attr("str") < level / 4 ) {
	tell_object(me, HIW "由於你勤練鎚法﹐你的膂力提高了。\n" NOR);
	me->add("str", 1);
    }
}
