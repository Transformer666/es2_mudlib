// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("notraces");
    setup();
}

int valid_enable(string usage)
{
    return usage == "dodge";
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("notraces", 1);
    learn = me->query_learn("notraces");

    if( !skill ) {
        if( learn >= 1500 ) {
            tell_object(me,
                HIY "你感覺行走間不留痕跡﹐無痕步已經練成了﹗\n" NOR);
            me->advance_skill("notraces", 40);
            me->gain_score("martial art", 500);
        }
        return;
    }

    if( (skill < 120) && (skill-39) * (skill-39) * 200 < learn - 1500 ) {
        me->advance_skill("notraces", 1);
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
        tell_object(me, HIW "由於你無痕步的修練有成﹐你的敏捷提高了。\n" NOR);
        me->add("dex", 1);
    }
}
