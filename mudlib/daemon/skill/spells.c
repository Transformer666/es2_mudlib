// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("spells");
    setup();
}

int valid_enable(string usage)
{
    return usage == "spells";
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("spells", 1);
    learn = me->query_learn("spells");

    if( !skill ) {
        if( learn >= 1500 ) {
            tell_object(me,
                HIY "你感覺你感覺自己對法術的掌握更加純熟了﹗\n" NOR);
            me->advance_skill("spells", 40);
            me->gain_score("martial art", 500);
        }
        return;
    }

    if( (skill < 120) && (skill-39) * (skill-39) * 200 < learn - 1500 ) {
        me->advance_skill("spells", 1);
        me->gain_score("martial art", (skill+1) * 10);
        if( skill >= 50 )
            me->gain_score("martial mastery", (skill-40) * 10);
    }
}

void skill_advanced(object me, string sk)
{
    int level;

    level = me->query_skill(sk, 1);
    if( level % 10 == 9 && me->query_attr("int") < level / 3 ) {
        tell_object(me, HIW "由於你法術的修練有成﹐你的悟性提高了。\n" NOR);
        me->add("int", 1);
    }
}
