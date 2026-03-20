// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N施展「妙手回春」﹐$w精準地點向$n的$l經脈",
    "dodge":		-5,
    "damae":		8,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N一式「銀蛇吐信」﹐$w如靈蛇般射向$n的$l",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N凌空飛出「天外飛針」﹐$w從刁鑽角度刺向$n的$l",
    "dodge":		-15,
    "damage":		15,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N身法飄忽﹐「穿花蝴蝶」的$w輕盈地沒入$n的$l穴道",
    "dodge":		10,
    "damae":		5,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N遠距發針﹐「百步穿楊」的$w破空射向$n的$l",
    "dodge":		-10,
    "damage":		12,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N使出「神針渡穴」﹐$w帶著渾厚內力刺入$n的$l要穴",
    "dodge":		5,
    "damae":		10,
    "damage_type":	"刺傷"
  ]),
});

string *interattack = ({
  "$N手中銀針閃爍﹐奇針手法令人防不勝防。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("amazing needle");
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

  damage = COMBAT_D->fight(me, opponent, "amazing needle", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("amazing needle", 1);
    learn = me->query_learn("amazing needle");

    if( !skill ) {
	if( learn >= 1500 ) {
	    tell_object(me,
		HIY "你感覺奇針術的招式已經融會貫通﹗\n" NOR);
	    me->advance_skill("amazing needle", 40);
	    me->gain_score("martial art", 500);
	}
	return;
    }

    if( (skill < 120) && (skill-39) * (skill-39) * 200 < learn - 1500 ) {
	me->advance_skill("amazing needle", 1);
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
	tell_object(me, HIW "由於你奇針術的修練有成﹐你的敏捷提高了。\n" NOR);
	me->add("dex", 1);
    }
}
