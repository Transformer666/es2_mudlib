// vim: syntax=lpc
// mystsword.c - 小步玄劍（劍法技能）

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
    ([
        "name":         "暮雪三嘆",
        "action":       "$N使一招「暮雪三嘆」，手中$w急如驟雨般地刺向$n$l",
        "dodge":        -30,
        "damae":        60,
        "damage_type":  "刺傷",
    ]),
    ([
        "name":         "處子弄笛",
        "action":       "$N身形一晃，一招「處子弄笛」向$n$l刺出一劍",
        "dodge":        -20,
        "damae":        80,
        "damage_type":  "刺傷",
    ]),
    ([
        "name":         "陽谷白練",
        "action":       "$N舞動$w，一招「陽谷白練」挾著閃閃劍光刺向$n的$l",
        "dodge":        -40,
        "damage_type":  "刺傷",
    ]),
    ([
        "name":         "薰容逐電",
        "action":       "$N手中$w一個圈轉，使出「薰容逐電」中鋒直進刺向$n的$l",
        "dodge":        -30,
        "damae":        100,
        "damage_type":  "刺傷",
    ]),
});

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("mystsword");
}

int valid_enable(string usage)
{
    return usage == "sword" || usage == "parry";
}

int valid_learn(object me)
{
    object ob;

    if( (int)me->query_skill("mystforce", 1) < 30 )
        return notify_fail("你的步玄心法火候還不夠。\n");

    if( (int)me->query("max_force") < 100 )
        return notify_fail("你的內力不夠，沒有辦法練小步玄劍。\n");

    if( !(ob = me->query_temp("weapon"))
    ||  (string)ob->query("skill_type") != "sword" )
        return notify_fail("你必須先找一把劍才能練劍法。\n");

    return 1;
}

mapping query_action(object me, object weapon)
{
    return actions[random(sizeof(actions))];
}

int practice_skill(object me)
{
    if( (int)me->query("kee") < 30
    ||  (int)me->query("force") < 5 )
        return notify_fail("你的內力或氣不夠，沒有辦法練習小步玄劍。\n");
    me->receive_damage("kee", 30);
    me->add("force", -5);
    write("你按著所學練了一遍小步玄劍。\n");
    return 1;
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("mystsword", 1);
    learn = me->query_learn("mystsword");

    if( !skill ) {
        if( learn >= 500 ) {
            tell_object(me,
                HIY "你覺得手中劍法已經融會貫通，小步玄劍的技巧已有所領悟！\n" NOR);
            me->advance_skill("mystsword", 1);
        }
        return;
    }

    if( (skill < 120) && (skill) * (skill) * 100 < learn - 500 ) {
        me->advance_skill("mystsword", 1);
        me->gain_score("martial art", (skill+1) * 5);
    }
}

void skill_advanced(object me, string sk)
{
    int level;

    level = me->query_skill(sk, 1);
    if( level % 10 == 9 && me->query_attr("dex") < level / 3 ) {
        tell_object(me, HIW "由於你勤練小步玄劍，你的敏捷提高了。\n" NOR);
        me->add("dex", 1);
    }
}
