// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

string *parry_msg = ({
    "只聽見「鏘」一聲，被$p格開了。\n",
    "結果「當」地一聲被$p擋開了。\n",
    "但是被$n用手中兵刃架開。\n",
    "但是$n身子一側，用手中兵刃格開。\n",
});

string *unarmed_parry_msg = ({
    "但是被$p格開了。\n",
    "結果被$p擋開了。\n",
});

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("parry");
    setup();
}

string query_parry_msg(object weapon)
{
    if( weapon )
	return parry_msg[random(sizeof(parry_msg))];
    else
	return unarmed_parry_msg[random(sizeof(unarmed_parry_msg))];
}

varargs int
parry_using(object me, int ability, int strength, object from)
{
    int parry_skill, absorbed;

    parry_skill = me->query_skill("parry");
    absorbed = strength * parry_skill / (parry_skill + ability + 1);

    // Chance to improve parry skill when successfully parrying
    if( parry_skill < ability && userp(me) ) {
	me->improve_skill("parry", 1);
    }

    return absorbed;
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("parry", 1);
    learn = me->query_learn("parry");

    if( !skill ) {
	if( learn >= 500 ) {
	    tell_object(me,
		HIY "你覺得自己招架的技巧已有所領悟﹗\n" NOR);
	    me->advance_skill("parry", 1);
	}
	return;
    }

    if( (skill < 120) && (skill) * (skill) * 100 < learn - 500 ) {
	me->advance_skill("parry", 1);
	me->gain_score("martial art", (skill+1) * 5);
    }
}

void skill_advanced(object me, string sk)
{
    int level;

    level = me->query_skill(sk, 1);
    if( level % 10 == 9 && me->query_attr("cps") < level / 3 ) {
	tell_object(me, HIW "由於你勤練招架﹐你的定力提高了。\n" NOR);
	me->add("cps", 1);
    }
}

int valid_enable(string usage)
{
    return usage == "parry";
}
