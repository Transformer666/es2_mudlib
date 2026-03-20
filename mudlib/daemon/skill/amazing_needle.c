// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N出手如電﹐$w瞬間刺入$n的$l經脈",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N雙指一彈﹐$w帶著驚人勁力射向$n的$l",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N身法詭異地閃到$n身側﹐$w直取$n的$l命穴",
    "dodge":		5,
    "damage":		10,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N冷笑一聲﹐$w劃出驚異弧線刺向$n的$l",
    "dodge":		-15,
    "damage":		15,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N手中$w忽然化為兩道銀光﹐同時射向$n的$l",
    "dodge":		-10,
    "damage":		15,
    "damage_type":	"刺傷"
  ]),
  ([
    "action":		"$N虛實難辨地一晃﹐$w已然沒入$n的$l穴道",
    "dodge":		10,
    "damage":		5,
    "damage_type":	"刺傷"
  ]),
});

string *interattack = ({
  "$N指間$n閃爍寒光﹐令人不寒而慄。\n",
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
