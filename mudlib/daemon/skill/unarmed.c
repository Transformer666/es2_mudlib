// vim: syntax=lpc
#pragma save_binary

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
  ([
    "action":		"$N握緊拳頭往$n的$l用力揮出",
    "dodge":		-5,
    "damae":		5,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N抬腿往$n的$l踢去",
    "dodge":		-10,
    "damae":		10,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N抓住機會往$n的$l揮了一拳",
    "dodge":		-5,
    "damae":		5,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N放低身子﹐對準$n的$l一拳揮出",
    "dodge":		10,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N大叫一聲，往$n的$l踢出一腿",
    "dodge":		-10,
    "damage":		10,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N跳了起來，往$n的$l飛踢過去",
    "dodge":		5,
    "damage":		5,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N做了個閃避假動作，冷不防一拳往$n$l揮去",
    "dodge":		-5,
    "damage":		10,
    "damage_type":	"瘀傷"
  ]),
  ([
    "action":		"$N假裝要後退，忽然蹲低身子向$n$l踢了一腳",
    "dodge":		10,
    "damage":		5,
    "damage_type":	"瘀傷"
  ]),
});

string *interattack = ({
  "$N緊盯著$n的一舉一動。\n",
  "$N虛張聲勢地揮舞著拳頭。\n",
  "$N一邊緩緩移動，一邊想要找出可以進攻的空隙。\n",
});

private void
create()
{
  seteuid(getuid());
  DAEMON_D->register_skill_daemon("unarmed");
  setup();
}

void
attack_using (object me, object opponent, string skill)
{
  int damage;

  if (!opponent)
    {
      if (me->query_temp("last_attacked_target"))
	message_vision (CYN + interattack[random(sizeof(interattack))] + NOR, me, opponent);
      return;
    }

  damage = COMBAT_D->fight(me, opponent, "unarmed", actions[random(sizeof(actions))]);
}

int
valid_enable (string usage)
{
  return 0;
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("unarmed", 1);
    learn = me->query_learn("unarmed");

    if( !skill ) {
	if( learn >= 500 ) {
	    tell_object(me,
		HIY "你覺得自己的拳腳功夫已有所領悟﹗\n" NOR);
	    me->advance_skill("unarmed", 1);
	}
	return;
    }

    if( (skill < 120) && (skill) * (skill) * 100 < learn - 500 ) {
	me->advance_skill("unarmed", 1);
	me->gain_score("martial art", (skill+1) * 5);
    }
}

void skill_advanced(object me, string sk)
{
    int level;

    level = me->query_skill(sk, 1);
    if( level % 10 == 9 && me->query_attr("str") < level / 4 ) {
	tell_object(me, HIW "由於你勤練武藝﹐你的膂力提高了。\n" NOR);
	me->add("str", 2);
    }
}

