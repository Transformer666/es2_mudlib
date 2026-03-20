// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

string *dodge_msg = ({
    "但是和$p$l偏了幾寸。\n",
    "但是被$p機靈地躲開了。\n",
    "但是$n身子一側，閃了開去。\n",
    "但是被$p及時避開。\n",
    "但是$n已有準備，不慌不忙的躲開。\n",
});

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("dodge");
    setup();
}

string query_dodge_msg()
{
    return dodge_msg[random(sizeof(dodge_msg))];
}

varargs int
dodge_using(object me, int ability, int strength, object from)
{
    int dodge_skill;

    dodge_skill = me->query_skill("dodge");

    // Chance to improve dodge skill when successfully defending
    if( dodge_skill < ability && userp(me) ) {
	me->improve_skill("dodge", 1);
    }

    return dodge_skill / 2;
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("dodge", 1);
    learn = me->query_learn("dodge");

    if( !skill ) {
	if( learn >= 500 ) {
	    tell_object(me,
		HIY "你覺得自己的身法靈活了許多﹐閃避的技巧已有所領悟﹗\n" NOR);
	    me->advance_skill("dodge", 1);
	}
	return;
    }

    if( (skill < 120) && (skill) * (skill) * 100 < learn - 500 ) {
	me->advance_skill("dodge", 1);
	me->gain_score("martial art", (skill+1) * 5);
    }
}

void skill_advanced(object me, string sk)
{
    int level;

    level = me->query_skill(sk, 1);
    if( level % 10 == 9 && me->query_attr("dex") < level / 3 ) {
	tell_object(me, HIW "由於你勤練閃避﹐你的敏捷提高了。\n" NOR);
	me->add("dex", 1);
    }
}

int valid_enable(string usage)
{
    return usage == "dodge";
}
