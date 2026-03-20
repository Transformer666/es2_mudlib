// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
    ([
        "action":       "$N一式「雲捲長空」﹐$w如捲雲般橫掃$n的$l",
        "dodge":        -5,
        "damae":        8,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N棍影朦朧﹐使出「霧鎖蒼穹」﹐$w罩向$n的$l",
        "dodge":        5,
        "damae":        5,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N身隨棍走﹐「行雲流水」﹐$w輕靈點向$n的$l",
        "dodge":        10,
        "damage":       5,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N棍勢驟變﹐一招「翻雲覆雨」﹐$w猛力砸向$n的$l",
        "dodge":        -15,
        "damage":       15,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N大喝一聲﹐使出「撥雲見日」﹐$w直搗$n的$l",
        "dodge":        -10,
        "damage":       12,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N身形飄動﹐「風起雲湧」﹐$w連環掃向$n的$l",
        "dodge":        -5,
        "damae":        10,
        "damage_type":  "瘀傷"
    ]),
});

string *interattack = ({
    "$N持棍在手﹐棍影如行雲般飄逸。\n",
});

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("cloudstaff");
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

    damage = COMBAT_D->fight(me, opponent, "cloudstaff", actions[random(sizeof(actions))], weapon);
}

int
valid_enable(string usage)
{
    return 0;
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("cloudstaff", 1);
    learn = me->query_learn("cloudstaff");

    if( !skill ) {
        if( learn >= 1500 ) {
            tell_object(me,
                HIY "你感覺雲棍法的招式已經融會貫通﹗\n" NOR);
            me->advance_skill("cloudstaff", 40);
            me->gain_score("martial art", 500);
        }
        return;
    }

    if( (skill < 120) && (skill-39) * (skill-39) * 200 < learn - 1500 ) {
        me->advance_skill("cloudstaff", 1);
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
        tell_object(me, HIW "由於你雲棍法的修練有成﹐你的臂力提高了。\n" NOR);
        me->add("str", 1);
    }
}
