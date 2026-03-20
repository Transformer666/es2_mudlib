// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
    ([
        "action":       "$N一式「雪舞狂飆」﹐$w如暴風雪般抽向$n的$l",
        "dodge":        -5,
        "damae":        5,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N鞭影一閃﹐使出「冰鏈縛天」﹐$w纏向$n的$l",
        "dodge":        -10,
        "damage":       10,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N身形旋轉﹐「寒風捲雪」﹐$w挾著寒氣掃向$n的$l",
        "dodge":        -15,
        "damage":       15,
        "damage_type":  "割傷"
    ]),
    ([
        "action":       "$N冷哼一聲﹐一招「凝霜纏身」﹐$w如蛇般纏向$n的$l",
        "dodge":        5,
        "damae":        8,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N連環出鞭﹐使出「飛雪連環」﹐$w接連抽向$n的$l",
        "dodge":        -5,
        "damage":       12,
        "damage_type":  "割傷"
    ]),
    ([
        "action":       "$N猛然揮鞭﹐「冰河裂岸」﹐$w帶著破空之聲砸向$n的$l",
        "dodge":        10,
        "damae":        7,
        "damage_type":  "瘀傷"
    ]),
});

string *interattack = ({
    "$N揮動雪鞭﹐鞭影如漫天飛雪。\n",
});

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("snowwhip");
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

    damage = COMBAT_D->fight(me, opponent, "snowwhip", actions[random(sizeof(actions))], weapon);
}

int
valid_enable(string usage)
{
    return 0;
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("snowwhip", 1);
    learn = me->query_learn("snowwhip");

    if( !skill ) {
        if( learn >= 1500 ) {
            tell_object(me,
                HIY "你感覺雪鞭法的招式已經融會貫通﹗\n" NOR);
            me->advance_skill("snowwhip", 40);
            me->gain_score("martial art", 500);
        }
        return;
    }

    if( (skill < 120) && (skill-39) * (skill-39) * 200 < learn - 1500 ) {
        me->advance_skill("snowwhip", 1);
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
        tell_object(me, HIW "由於你雪鞭法的修練有成﹐你的敏捷提高了。\n" NOR);
        me->add("dex", 1);
    }
}
