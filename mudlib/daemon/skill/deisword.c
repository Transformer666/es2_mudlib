// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
    ([
        "action":       "$N使一招「帝王斬邪」﹐$w帶著凜然正氣劈向$n的$l",
        "dodge":        -10,
        "damae":        12,
        "damage_type":  "割傷"
    ]),
    ([
        "action":       "$N施展「龍威震宇」﹐$w爆發出龍形劍氣刺向$n的$l",
        "dodge":        -5,
        "damae":        10,
        "damage_type":  "刺傷"
    ]),
    ([
        "action":       "$N威嚴一喝使出「天子臨朝」﹐$w如天威降臨般斬向$n的$l",
        "dodge":        -15,
        "damage":       15,
        "damage_type":  "割傷"
    ]),
    ([
        "action":       "$N身形飄然亮出「御劍乘風」﹐$w乘風而至直取$n的$l",
        "dodge":        5,
        "damae":        8,
        "damage_type":  "刺傷"
    ]),
    ([
        "action":       "$N劍光大盛使出「金殿飛光」﹐$w化作萬道金光射向$n的$l",
        "dodge":        0,
        "damage":       10,
        "damage_type":  "割傷"
    ]),
    ([
        "action":       "$N氣勢磅礡施展「萬乘之尊」﹐$w以壓倒性的氣勢劃向$n的$l",
        "dodge":        10,
        "damae":        7,
        "damage_type":  "刺傷"
    ]),
});

string *interattack = ({
    "$N持劍在手﹐帝劍散發出威嚴的劍氣。\n",
});

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("deisword");
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

    damage = COMBAT_D->fight(me, opponent, "deisword", actions[random(sizeof(actions))], weapon);
}

int
valid_enable(string usage)
{
    return 0;
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("deisword", 1);
    learn = me->query_learn("deisword");

    if( !skill ) {
        if( learn >= 1500 ) {
            tell_object(me,
                HIY "你感覺地煞劍法的招式已經融會貫通﹗\n" NOR);
            me->advance_skill("deisword", 40);
            me->gain_score("martial art", 500);
        }
        return;
    }

    if( (skill < 120) && (skill-39) * (skill-39) * 200 < learn - 1500 ) {
        me->advance_skill("deisword", 1);
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
        tell_object(me, HIW "由於你地煞劍法的修練有成﹐你的敏捷提高了。\n" NOR);
        me->add("dex", 1);
    }
}
