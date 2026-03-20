// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("literate");
    setup();
}

int valid_enable(string usage)
{
    return usage == "literate";
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("literate", 1);
    learn = me->query_learn("literate");

    if( !skill ) {
        if( learn >= 300 ) {
            tell_object(me,
                HIY "你覺得自己識字的能力已有所領悟﹗\n" NOR);
            me->advance_skill("literate", 1);
        }
        return;
    }

    if( (skill < 120) && (skill) * (skill) * 100 < learn - 300 ) {
        me->advance_skill("literate", 1);
        me->gain_score("martial art", (skill+1) * 5);
    }
}

void skill_advanced(object me, string sk)
{
    int level;

    level = me->query_skill(sk, 1);
    if( level % 10 == 9 && me->query_attr("int") < level / 4 ) {
        tell_object(me, HIW "由於你勤練識字﹐你的悟性提高了。\n" NOR);
        me->add("int", 1);
    }
}
