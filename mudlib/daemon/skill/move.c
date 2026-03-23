// vim: syntax=lpc
// move.c - 身法技能

#include <ansi.h>

inherit SKILL;

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("move");
    setup();
}

int valid_enable(string usage)
{
    return usage == "move";
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("move", 1);
    learn = me->query_learn("move");

    if( !skill ) {
	if( learn >= 500 ) {
	    tell_object(me,
		HIY "你覺得自己的身法靈活了許多﹐移動的技巧已有所領悟﹗\n" NOR);
	    me->advance_skill("move", 1);
	}
	return;
    }

    if( (skill < 120) && (skill) * (skill) * 100 < learn - 500 ) {
	me->advance_skill("move", 1);
	me->gain_score("martial art", (skill+1) * 5);
    }
}

void skill_advanced(object me, string sk)
{
    int level;

    level = me->query_skill(sk, 1);
    if( level % 10 == 9 && me->query_attr("dex") < level / 3 ) {
	tell_object(me, HIW "由於你勤練身法﹐你的敏捷提高了。\n" NOR);
	me->add("dex", 1);
    }
}
