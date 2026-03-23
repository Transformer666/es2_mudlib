// vim: syntax=lpc
// nine_moon.c - 九陰赤煉劍法（劍法技能）

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
    ([
        "name":         "陰魂不散",
        "action":       "$N使一招「陰魂不散」，手中$w劍光暴長，向$n的$l刺去",
        "dodge":        50,
        "damae":        170,
        "damage_type":  "刺傷",
    ]),
    ([
        "name":         "陰氣森森",
        "action":       "$N劍隨身轉，一招「陰氣森森」罩向$n的$l",
        "dodge":        -70,
        "damae":        20,
        "damage_type":  "刺傷",
    ]),
    ([
        "name":         "陰雲迭起",
        "action":       "$N舞動$w，一招「陰雲迭起」挾著無數劍光刺向$n的$l",
        "dodge":        -40,
        "damae":        90,
        "damage_type":  "刺傷",
    ]),
    ([
        "name":         "陰曹地府",
        "action":       "$N手中$w龍吟一聲，祭出「陰曹地府」往$n的$l刺出數劍",
        "dodge":        -40,
        "damae":        40,
        "damage_type":  "刺傷",
    ]),
    ([
        "name":         "陰陽兩儀",
        "action":       "$N手中$w劍光暴長，一招「陰陽兩儀」往$n$l刺去",
        "dodge":        60,
        "damae":        120,
        "damage_type":  "刺傷",
    ]),
    ([
        "name":         "陰日陽月",
        "action":       "$N手中$w化成一道光弧，直指$n$l，一招「陰日陽月」發出虎嘯龍吟刺去",
        "dodge":        -60,
        "damae":        150,
        "damage_type":  "刺傷",
    ]),
});

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("nine moon");
}

int valid_enable(string usage)
{
    return usage == "sword" || usage == "parry";
}

int valid_learn(object me)
{
    object ob;

    if( (string)me->query("gender") != "女性" )
        return notify_fail("九陰赤煉劍法是只有女子才能練的武功。\n");

    if( (int)me->query("max_force") < 50 )
        return notify_fail("你的內力不夠，沒有辦法練九陰赤煉劍法。\n");

    if( (string)me->query_skill_mapped("force") != "nine_moon_force" )
        return notify_fail("九陰赤煉劍法必須配合九陰心經才能練。\n");

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
        return notify_fail("你的內力或氣不夠，沒有辦法練習九陰赤煉劍。\n");
    me->receive_damage("kee", 30);
    me->add("force", -5);
    write("你按著所學練了一遍九陰赤煉劍法。\n");
    return 1;
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("nine moon", 1);
    learn = me->query_learn("nine moon");

    if( !skill ) {
        if( learn >= 500 ) {
            tell_object(me,
                HIY "你覺得手中劍法已經融會貫通，九陰赤煉劍法的技巧已有所領悟！\n" NOR);
            me->advance_skill("nine moon", 1);
        }
        return;
    }

    if( (skill < 120) && (skill) * (skill) * 100 < learn - 500 ) {
        me->advance_skill("nine moon", 1);
        me->gain_score("martial art", (skill+1) * 5);
    }

    if( (int)me->query_skill("nine moon", 1) % 10 == 0 ) {
        tell_object(me,
            RED "\n你突然覺得一股陰氣衝上心頭，只覺得想殺人....\n\n" NOR);
        me->add("bellicosity", 2000);
    } else
        me->add("bellicosity", 200);
}

void skill_advanced(object me, string sk)
{
    int level;

    level = me->query_skill(sk, 1);
    if( level % 10 == 9 && me->query_attr("dex") < level / 3 ) {
        tell_object(me, HIW "由於你勤練九陰赤煉劍法，你的敏捷提高了。\n" NOR);
        me->add("dex", 1);
    }
}
