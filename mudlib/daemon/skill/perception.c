// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("perception");
    setup();
}

int valid_enable(string usage)
{
    return usage == "perception";
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("perception", 1);
    learn = me->query_learn("perception");

    if( !skill ) {
        if( learn >= 500 ) {
            tell_object(me,
                HIY "你覺得自己的感知能力已有所領悟﹗\n" NOR);
            me->advance_skill("perception", 1);
        }
        return;
    }

    if( (skill < 120) && (skill) * (skill) * 100 < learn - 500 ) {
        me->advance_skill("perception", 1);
        me->gain_score("martial art", (skill+1) * 5);
    }
}

void skill_advanced(object me, string sk)
{
    int level;

    level = me->query_skill(sk, 1);
    if( level % 10 == 9 && me->query_attr("wis") < level / 4 ) {
        tell_object(me, HIW "由於你勤練感知﹐你的悟性提高了。\n" NOR);
        me->add("wis", 1);
    }
}
