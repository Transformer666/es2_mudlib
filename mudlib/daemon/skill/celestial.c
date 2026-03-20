// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

void create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("celestial");
}

int valid_enable(string usage)
{
    return usage == "force";
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("celestial", 1);
    learn = me->query_learn("celestial", 1);

    if( !skill ) {
        if( learn >= 1500 ) {
            tell_object(me,
                HIY "你感覺體內氣息調和﹐天仙內功的內功已經練成了﹗\n" NOR);
            me->advance_skill("celestial", 40);
            me->gain_score("martial art", 500);
        }
        return;
    }

    if( (skill < 120) && (skill-39) * (skill-39) * 200 < learn - 1500 ) {
        me->advance_skill("celestial", 1);
        me->gain_score("martial art", (skill+1) * 10);
        if( skill >= 50 )
            me->gain_score("martial mastery", (skill-40) * 10);
    }
}

void skill_advanced(object me, string sk)
{
    int level;

    level = me->query_skill(sk, 1);
    if( me->query_stat_maximum("gin") < level * 14 )
        me->advance_stat("gin", 4);
    if( me->query_stat_maximum("kee") < level * 14 )
        me->advance_stat("kee", 5);
    if( me->query_stat_maximum("sen") < level * 16 )
        me->advance_stat("sen", 6);
}

int do_exercise(object me)
{
    if( me->query_stat("gin") < 10
    ||  me->query_stat("kee") < 10
    ||  me->query_stat("sen") < 10 ) {
        tell_object(me, "你覺得神困力乏﹐沒有辦法繼續練功了。\n");
        me->interrupt_me(me, "exhausted");
        return 1;
    }
    me->consume_stat("gin", 10);
    me->consume_stat("kee", 10);
    me->consume_stat("sen", 10);

    if( random(me->query_attr("spi") + me->query_attr("wis") + me->query_skill("force", 1)) > 20 ) {
        me->damage_stat("gin", 1);
        me->damage_stat("kee", 1);
        me->damage_stat("sen", 1);
        me->improve_skill("celestial", random(me->query_attr("spi")/10) + 1);
        me->improve_skill("force", random(me->query_attr("wis")/10) + 1);
    }
    return 1;
}

int halt_exercise(object me, object owner, object from, string how)
{
    return 1;
}

varargs int
exert_function(object me, string func, object target)
{
    switch(func) {
    case "celestial":
        message_vision(HIY "$N盤膝而坐﹐運起天仙內功﹐氣息空靈飄渺。\n" NOR,
            me);
        me->start_busy((: do_exercise, me :), (: halt_exercise, me :));
        return 1;
    default:
        return notify_fail("天仙內功沒有這種功能。\n");
    }
}
