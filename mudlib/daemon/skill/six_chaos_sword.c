// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
    ([
        "action":       "$N使一招「亂花迷眼」﹐$w幻化出數道劍影刺向$n的$l",
        "dodge":        5,
        "damae":        8,
        "damage_type":  "刺傷"
    ]),
    ([
        "action":       "$N施展「顛倒乾坤」﹐$w忽上忽下地劈向$n的$l",
        "dodge":        -10,
        "damae":        12,
        "damage_type":  "割傷"
    ]),
    ([
        "action":       "$N猛然使出「混沌初開」﹐$w爆發出狂亂的劍氣斬向$n的$l",
        "dodge":        -15,
        "damage":       15,
        "damage_type":  "割傷"
    ]),
    ([
        "action":       "$N身形飄忽亮出「迷途劍影」﹐$w從意想不到的角度刺向$n的$l",
        "dodge":        10,
        "damae":        7,
        "damage_type":  "刺傷"
    ]),
    ([
        "action":       "$N劍勢一變使出「六道輪迴」﹐$w連環六擊攻向$n的$l",
        "dodge":        -5,
        "damage":       10,
        "damage_type":  "刺傷"
    ]),
    ([
        "action":       "$N旋身施展「天旋地轉」﹐$w化作一團劍旋劃向$n的$l",
        "dodge":        0,
        "damae":        10,
        "damage_type":  "割傷"
    ]),
});

string *interattack = ({
    "$N持劍在手﹐劍招變幻莫測﹐令人眼花繚亂。\n",
});

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("six chaos sword");
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

    damage = COMBAT_D->fight(me, opponent, "six chaos sword", actions[random(sizeof(actions))], weapon);
}

int
valid_enable(string usage)
{
    return 0;
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("six chaos sword", 1);
    learn = me->query_learn("six chaos sword");

    if( !skill ) {
        if( learn >= 1500 ) {
            tell_object(me,
                HIY "你感覺六亂劍法的招式已經融會貫通﹗\n" NOR);
            me->advance_skill("six chaos sword", 40);
            me->gain_score("martial art", 500);
        }
        return;
    }

    if( (skill < 120) && (skill-39) * (skill-39) * 200 < learn - 1500 ) {
        me->advance_skill("six chaos sword", 1);
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
        tell_object(me, HIW "由於你六亂劍法的修練有成﹐你的敏捷提高了。\n" NOR);
        me->add("dex", 1);
    }
}
