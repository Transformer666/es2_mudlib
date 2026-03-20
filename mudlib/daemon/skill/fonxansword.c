// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
    ([
        "action":       "$N使一招「封山絕壁」﹐$w如山嶽般沉穩地劈向$n的$l",
        "dodge":        -10,
        "damae":        10,
        "damage_type":  "割傷"
    ]),
    ([
        "action":       "$N施展「崖前望月」﹐$w凌空一轉刺向$n的$l",
        "dodge":        5,
        "damae":        8,
        "damage_type":  "刺傷"
    ]),
    ([
        "action":       "$N大喝一聲使出「石破天驚」﹐$w猛然砸向$n的$l",
        "dodge":        -15,
        "damage":       15,
        "damage_type":  "割傷"
    ]),
    ([
        "action":       "$N身形一晃亮出「山嵐裂風」﹐$w帶著破風之勢斬向$n的$l",
        "dodge":        -5,
        "damae":        12,
        "damage_type":  "割傷"
    ]),
    ([
        "action":       "$N劍走偏鋒使出「峰迴劍影」﹐$w繞過防禦直取$n的$l",
        "dodge":        10,
        "damage":       7,
        "damage_type":  "刺傷"
    ]),
    ([
        "action":       "$N縱身躍起施展「嶺上飛虹」﹐$w化作一道虹光劃向$n的$l",
        "dodge":        0,
        "damae":        10,
        "damage_type":  "割傷"
    ]),
});

string *interattack = ({
    "$N持劍在手﹐封山劍法的劍意如山嶽般沉穩。\n",
});

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("fonxansword");
    setup();
}

void
attack_using(object me, object opponent, object weapon)
{
    int damage;

    if( !opponent ) {
        if( me->query_temp("last_attacked_target") )
            message_vision(CYN + interattack[random(sizeof(interattack))] + NOR, me, weapon);
        return;
    }

    damage = COMBAT_D->fight(me, opponent, "fonxansword", actions[random(sizeof(actions))], weapon);
}

int
valid_enable(string usage)
{
    return 0;
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("fonxansword", 1);
    learn = me->query_learn("fonxansword");

    if( !skill ) {
        if( learn >= 1500 ) {
            tell_object(me,
                HIY "你感覺封山劍法的招式已經融會貫通﹗\n" NOR);
            me->advance_skill("fonxansword", 40);
            me->gain_score("martial art", 500);
        }
        return;
    }

    if( (skill < 120) && (skill-39) * (skill-39) * 200 < learn - 1500 ) {
        me->advance_skill("fonxansword", 1);
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
        tell_object(me, HIW "由於你封山劍法的修練有成﹐你的敏捷提高了。\n" NOR);
        me->add("dex", 1);
    }
}
