// vim: syntax=lpc
// music - 音律

#include <ansi.h>

inherit SKILL;

string type() { return "knowledge"; }

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("music");
    setup();
}

int valid_enable(string usage)
{
    return usage == "music";
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("music", 1);
    learn = me->query_learn("music");

    if( !skill ) {
        if( learn >= 300 ) {
            tell_object(me,
                HIY "你覺得自己對音律之學已有所領悟！\n" NOR);
            me->advance_skill("music", 1);
        }
        return;
    }

    if( (skill < 120) && (skill) * (skill) * 100 < learn - 300 ) {
        me->advance_skill("music", 1);
        me->gain_score("martial art", (skill+1) * 5);
    }
}

void skill_advanced(object me, string sk)
{
    int level;

    level = me->query_skill(sk, 1);
    if( level % 10 == 9 && me->query_attr("spi") < level / 4 ) {
        tell_object(me, HIW "由於你學習音律之學有成，你的靈性提高了。\n" NOR);
        me->add("spi", 2);
    }
}
