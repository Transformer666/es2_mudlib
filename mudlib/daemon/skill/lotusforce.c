// vim: syntax=lpc
// lotusforce.c — 蓮華心法（寶蓮寺內功）

#include <ansi.h>

inherit SKILL;

void create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("lotusforce");
}

int valid_enable(string usage)
{
    return usage == "force";
}

int valid_learn(object me)
{
    if( (int)me->query_skill("buddhism") < (int)me->query_skill("lotusforce") )
        return notify_fail("你的大乘佛法修為不夠﹐無法領會更高深的蓮華心法。\n");

    return 1;
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("lotusforce", 1);
    learn = me->query_learn("lotusforce", 1);

    if( !skill ) {
        if( learn >= 1500 ) {
            tell_object(me,
                HIY "你感覺體內氣息調和﹐蓮華心法的內功已經練成了﹗\n" NOR);
            me->advance_skill("lotusforce", 40);
            me->gain_score("martial art", 500);
        }
        return;
    }

    if( (skill < 120) && (skill-39) * (skill-39) * 200 < learn - 1500 ) {
        me->advance_skill("lotusforce", 1);
        me->gain_score("martial art", (skill+1) * 10);
        if( skill >= 50 )
            me->gain_score("martial mastery", (skill-40) * 10);
    }
}

void skill_advanced(object me, string sk)
{
    int level;

    level = me->query_skill(sk, 1);
    // 蓮華心法偏重精神和氣
    if( me->query_stat_maximum("gin") < level * 14 )
        me->advance_stat("gin", 5);
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

    if( random(me->query_attr("wis") + me->query_attr("int") + me->query_skill("force", 1)) > 20 ) {
        me->damage_stat("gin", 1);
        me->damage_stat("kee", 1);
        me->damage_stat("sen", 1);
        me->improve_skill("lotusforce", random(me->query_attr("wis")/10) + 1);
        me->improve_skill("force", random(me->query_attr("int")/10) + 1);
    }
    return 1;
}

int halt_exercise(object me, object owner, object from, string how)
{
    return 1;
}

// 原版 exert heal — 自身療傷
int do_heal(object me)
{
    if( me->is_fighting() )
        return notify_fail("戰鬥中運功療傷？找死嗎？\n");

    if( (int)me->query("force") - (int)me->query("max_force") < 50 )
        return notify_fail("你的真氣不夠。\n");

    if( (int)me->query("eff_kee") < (int)me->query("max_kee") / 2 )
        return notify_fail("你已經受傷過重﹐只怕一運真氣便有生命危險﹗\n");

    tell_object(me,
        HIW "你全身放鬆﹐坐下來開始運功療傷。\n" NOR);
    message("vision",
        HIW + me->name() + "坐下來運功療傷﹐臉上一陣紅一陣白﹐"
        "不久﹐吐出一口瘀血﹐臉色看起來好多了。\n" NOR,
        environment(me), me);

    me->receive_curing("kee", 10 + (int)me->query_skill("force") / 5);
    me->add("force", -50);
    me->set("force_factor", 0);

    return 1;
}

// 原版 exert lifeheal — 為他人療傷
int do_lifeheal(object me, object target)
{
    if( !target )
        return notify_fail("你要用真氣為誰療傷？\n");

    if( me->is_fighting() || target->is_fighting() )
        return notify_fail("戰鬥中無法運功療傷﹗\n");

    if( (int)me->query("force") - (int)me->query("max_force") < 150 )
        return notify_fail("你的真氣不夠。\n");

    if( (int)target->query("eff_kee") < (int)target->query("max_kee") / 5 )
        return notify_fail(target->name() + "已經受傷過重﹐經受不起你的真氣震盪﹗\n");

    message_vision(
        HIY "$N坐了下來運起內功﹐將手掌貼在$n背心﹐"
        "緩緩地將真氣輸入$n體內....\n\n"
        "過了不久﹐$N額頭上冒出豆大的汗珠﹐"
        "$n吐出一口瘀血﹐臉色看起來紅潤多了。\n" NOR,
        me, target);

    target->receive_curing("kee", 10 + (int)me->query_skill("force") / 3);
    me->add("force", -150);
    me->set("force_factor", 0);

    return 1;
}

varargs int
exert_function(object me, string func, object target)
{
    switch(func) {
    case "lotusforce":
        message_vision(HIY "$N盤膝而坐﹐運起蓮華心法﹐周身散發淡淡金光。\n" NOR,
            me);
        me->start_busy((: do_exercise, me :), (: halt_exercise, me :));
        return 1;
    case "heal":
        return do_heal(me);
    case "lifeheal":
        return do_lifeheal(me, target);
    default:
        return notify_fail("蓮華心法沒有這種功能。\n");
    }
}
