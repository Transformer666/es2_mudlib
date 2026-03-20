// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N持$n使出「破陣斬將」﹐大開大闔地劈向$n的$l",
    "dodge":		-10,
    "damae":		12,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N持$n施展「軍陣突擊」﹐如箭般突刺$n的$l",
    "dodge":		-15,
    "damage":		15,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N持$n使出「長驅直入」﹐勢不可擋地攻向$n的$l",
    "dodge":		-5,
    "damae":		9,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N持$n橫掃使出「鐵壁橫掃」﹐沉重地掃向$n的$l",
    "dodge":		-10,
    "damage":		13,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N持$n使出「衝鋒陷陣」﹐奮不顧身地衝向$n的$l",
    "dodge":		5,
    "damae":		7,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N持$n使出「兵法奇謀」﹐出其不意地攻向$n的$l",
    "dodge":		10,
    "damage":		6,
    "damage_type":	"割傷"
  ]),
});

string *interattack = ({
  "$N持$n在手﹐戰術招式穩健紮實﹐殺氣凜然。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("tactic");
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

  damage = COMBAT_D->fight(me, opponent, "tactic", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return usage == "command";
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("tactic", 1);
    learn = me->query_learn("tactic");

    if( !skill ) {
	if( learn >= 1500 ) {
	    tell_object(me,
		HIY "你感覺兵法戰術的招式已經融會貫通﹗\n" NOR);
	    me->advance_skill("tactic", 40);
	    me->gain_score("martial art", 500);
	}
	return;
    }

    if( (skill < 120) && (skill-39) * (skill-39) * 200 < learn - 1500 ) {
	me->advance_skill("tactic", 1);
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
	tell_object(me, HIW "由於你兵法戰術的修練有成﹐你的悟性提高了。\n" NOR);
	me->add("int", 1);
    }
}
