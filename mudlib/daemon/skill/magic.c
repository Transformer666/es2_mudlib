// vim: syntax=lpc
// magic.c - 法術知識技能

#include <ansi.h>

inherit SKILL;

string type() { return "knowledge"; }

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("magic");
    setup();
}

int valid_enable(string usage)
{
    return usage == "magic";
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("magic", 1);
    learn = me->query_learn("magic");

    if( !skill ) {
        if( learn >= 1500 ) {
            tell_object(me,
                HIY "你覺得自己對法術的理解已有所領悟！\n" NOR);
            me->advance_skill("magic", 1);
        }
        return;
    }

    if( (skill < 120) && (skill) * (skill) * 100 < learn - 1500 ) {
        me->advance_skill("magic", 1);
        me->gain_score("martial art", (skill+1) * 5);
    }
}

void skill_advanced(object me, string sk)
{
    int level;

    level = me->query_skill(sk, 1);
    if( level % 10 == 9 && me->query_attr("int") < level / 4 ) {
        tell_object(me, HIW "由於你勤練法術﹐你的悟性提高了。\n" NOR);
        me->add("int", 1);
    }
}
