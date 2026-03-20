// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
    ([
        "action":       "$N一式「金剛伏魔」﹐$w帶著千鈞之力砸向$n的$l",
        "dodge":        -10,
        "damage":       10,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N口宣佛號﹐使出「羅漢鎮邪」﹐$w橫掃$n的$l",
        "dodge":        -5,
        "damae":        8,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N棍影大盛﹐「佛光普照」﹐$w如金光般罩向$n的$l",
        "dodge":        5,
        "damage":       5,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N大喝一聲﹐一招「降龍伏虎」﹐$w猛力劈向$n的$l",
        "dodge":        -15,
        "damage":       15,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N怒目圓睜﹐使出「怒目金剛」﹐$w直搗$n的$l",
        "dodge":        -5,
        "damae":        12,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N持棍護身﹐一式「天王護法」﹐$w順勢掃向$n的$l",
        "dodge":        10,
        "damae":        7,
        "damage_type":  "瘀傷"
    ]),
});

string *interattack = ({
    "$N持棍在手﹐金剛棍法帶著一股沛然正氣。\n",
});

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("jingang staff");
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

    damage = COMBAT_D->fight(me, opponent, "jingang staff", actions[random(sizeof(actions))], weapon);
}

int
valid_enable(string usage)
{
    return 0;
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("jingang staff", 1);
    learn = me->query_learn("jingang staff");

    if( !skill ) {
        if( learn >= 1500 ) {
            tell_object(me,
                HIY "你感覺金剛棍法的招式已經融會貫通﹗\n" NOR);
            me->advance_skill("jingang staff", 40);
            me->gain_score("martial art", 500);
        }
        return;
    }

    if( (skill < 120) && (skill-39) * (skill-39) * 200 < learn - 1500 ) {
        me->advance_skill("jingang staff", 1);
        me->gain_score("martial art", (skill+1) * 10);
        if( skill >= 50 )
            me->gain_score("martial mastery", (skill-40) * 10);
    }
}

void skill_advanced(object me, string sk)
{
    int level;

    level = me->query_skill(sk, 1);
    if( level % 10 == 9 && me->query_attr("str") < level / 3 ) {
        tell_object(me, HIW "由於你金剛棍法的修練有成﹐你的臂力提高了。\n" NOR);
        me->add("str", 1);
    }
}
