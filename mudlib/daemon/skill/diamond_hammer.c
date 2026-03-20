// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N舉起$w﹐大喝一聲朝$n的$l猛力砸下",
    "dodge":		-10,
    "damage":		15,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N橫掃$w﹐沉重的鎚身掃向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N踏前一步﹐$w如金剛降魔般搗向$n的$l",
    "dodge":		-15,
    "damage":		15,
    "damage_type":	"砍傷"
  ]),
  ([
    "action":		"$N旋轉$w﹐借著旋轉之力砸向$n的$l",
    "dodge":		5,
    "damage":		10,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N口宣佛號﹐$w由上而下劈向$n的$l",
    "dodge":		-10,
    "damage":		15,
    "damage_type":	"砍傷"
  ]),
  ([
    "action":		"$N低喝一聲﹐$w直搗$n的$l﹐勢若千鈞",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"瘀傷"
  ]),
});

string *interattack = ({
  "$N雙手持$n﹐穩如泰山﹐一身金剛之氣。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("diamond hammer");
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

  damage = COMBAT_D->fight(me, opponent, "diamond hammer", actions[random(sizeof(actions))], weapon);
}

int
valid_enable (string usage)
{
  return 0;
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("diamond hammer", 1);
    learn = me->query_learn("diamond hammer");

    if( !skill ) {
	if( learn >= 1500 ) {
	    tell_object(me,
		HIY "你感覺金剛鎚法的招式已經融會貫通﹗\n" NOR);
	    me->advance_skill("diamond hammer", 40);
	    me->gain_score("martial art", 500);
	}
	return;
    }

    if( (skill < 120) && (skill-39) * (skill-39) * 200 < learn - 1500 ) {
	me->advance_skill("diamond hammer", 1);
	me->gain_score("martial art", (skill+1) * 10);
	if( skill >= 50 )
	    me->gain_score("martial mastery", (skill-40) * 10);
    }
}

void skill_advanced(object me, string sk)
{
    int level;

    level = me->query_skill(sk, 1);
    if( level % 10 == 9 && me->query_attr("str") < level / 3 ) {
	tell_object(me, HIW "由於你金剛鎚法的修練有成﹐你的膂力提高了。\n" NOR);
	me->add("str", 1);
    }
}
