// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("spider array");
    setup();
}

int valid_enable(string usage)
{
    return usage == "spider array";
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("spider array", 1);
    learn = me->query_learn("spider array");

    if( !skill ) {
        if( learn >= 1000 ) {
            tell_object(me,
                HIY "你覺得自己對蛛陣的掌握已有所領悟﹗\n" NOR);
            me->advance_skill("spider array", 1);
        }
        return;
    }

    if( (skill < 120) && (skill) * (skill) * 100 < learn - 1000 ) {
        me->advance_skill("spider array", 1);
        me->gain_score("martial art", (skill+1) * 5);
    }
}

void skill_advanced(object me, string sk)
{
    int level;

    level = me->query_skill(sk, 1);
    if( level % 10 == 9 && me->query_attr("int") < level / 4 ) {
        tell_object(me, HIW "由於你勤練蛛陣﹐你的悟性提高了。\n" NOR);
        me->add("int", 1);
    }
}
