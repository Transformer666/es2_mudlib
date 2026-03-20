// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("iron cloth");
    setup();
}

int valid_enable(string usage)
{
    return usage == "iron cloth";
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("iron cloth", 1);
    learn = me->query_learn("iron cloth");

    if( !skill ) {
        if( learn >= 1000 ) {
            tell_object(me,
                HIY "你覺得自己的鐵布衫功力已有所領悟﹗\n" NOR);
            me->advance_skill("iron cloth", 1);
        }
        return;
    }

    if( (skill < 120) && (skill) * (skill) * 100 < learn - 1000 ) {
        me->advance_skill("iron cloth", 1);
        me->gain_score("martial art", (skill+1) * 5);
    }
}

void skill_advanced(object me, string sk)
{
    int level;

    level = me->query_skill(sk, 1);
    if( level % 10 == 9 && me->query_attr("con") < level / 4 ) {
        tell_object(me, HIW "由於你勤練鐵布衫﹐你的體質提高了。\n" NOR);
        me->add("con", 1);
    }
}
