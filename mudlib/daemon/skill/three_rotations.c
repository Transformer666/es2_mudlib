// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N使出「天旋」﹐身形上旋如飛鳥﹐$w削向$n的$l",
    "dodge":		-5,
    "damae":		9,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N施展「地旋」﹐腳踏旋風﹐掃向$n的$l",
    "dodge":		-10,
    "damage":		12,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N使出「人旋」﹐身隨意轉攻向$n的$l",
    "dodge":		5,
    "damae":		7,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N三旋合一使出「三才歸一」﹐勁力匯聚轟向$n的$l",
    "dodge":		-15,
    "damage":		15,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N身形大旋使出「乾坤大挪移」﹐排山倒海地擊向$n的$l",
    "dodge":		-10,
    "damae":		13,
    "damage_type":	"割傷"
  ]),
  ([
    "action":		"$N飛身旋踢使出「玄門旋踢」﹐凌厲的腿風掃向$n的$l",
    "dodge":		10,
    "damage":		6,
    "damage_type":	"瘀傷"
  ]),
});

string *interattack = ({
  "$N擺出三旋的架式﹐身形旋轉如風。\n",
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
