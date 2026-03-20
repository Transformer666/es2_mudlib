// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N一式「一敗天靈」﹐$w如電光般點向$n的$l天靈穴",
    "dodge":		5,
    "damae":		5,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N施展「二敗膻中」﹐$w疾如閃電刺向$n的$l膻中穴",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N凝神運針﹐「三敗氣海」的$w無聲無息地沒入$n的$l",
    "dodge":		-5,
    "damae":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N虛晃一招﹐「四敗命門」的$w暗中取$n的$l命門穴",
    "dodge":		10,
    "damage":		5,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N使出「五敗神闕」﹐$w帶著致命寒光射向$n的$l神闕穴",
    "dodge":		-15,
    "damage":		15,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N五針齊發﹐「連環奪命」的$w如暴雨般刺入$n的$l各處要穴",
    "dodge":		-10,
    "damae":		12,
    "damage_type":	"刺傷"
  ]),
});

string *interattack = ({
  "$N手持銀針﹐五敗針法瞄準$n的要穴。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("five defeat needle");
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

  damage = COMBAT_D->fight(me, opponent, "five defeat needle", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("five defeat needle", 1);
    learn = me->query_learn("five defeat needle");

    if( !skill ) {
	if( learn >= 1500 ) {
	    tell_object(me,
		HIY "你感覺五敗針法的招式已經融會貫通﹗\n" NOR);
	    me->advance_skill("five defeat needle", 40);
	    me->gain_score("martial art", 500);
	}
	return;
    }

    if( (skill < 120) && (skill-39) * (skill-39) * 200 < learn - 1500 ) {
	me->advance_skill("five defeat needle", 1);
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
	tell_object(me, HIW "由於你五敗針法的修練有成﹐你的敏捷提高了。\n" NOR);
	me->add("dex", 1);
    }
}
