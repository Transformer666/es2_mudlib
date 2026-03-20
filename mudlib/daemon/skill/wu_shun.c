// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
    ([
        "action":       "$N使出「順水推舟」﹐借勢將拳力推向$n的$l",
        "dodge":        5,
        "damae":        7,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N施展「借力打力」﹐巧妙地將力道反彈向$n的$l",
        "dodge":        10,
        "damage":       8,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N使出「四兩撥千斤」﹐輕描淡寫地擊向$n的$l",
        "dodge":        -5,
        "damae":        10,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N施展「以柔克剛」﹐柔勁暗湧攻向$n的$l",
        "dodge":        -10,
        "damage":       12,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N身隨意動使出「行雲流水」﹐拳勢綿綿不絕地打向$n的$l",
        "dodge":        -5,
        "damae":        9,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N氣勢大盛使出「勢如破竹」﹐摧枯拉朽地轟向$n的$l",
        "dodge":        -15,
        "damage":       15,
        "damage_type":  "瘀傷"
    ]),
});

string *interattack = ({
    "$N擺出武順的起手式﹐招式渾然天成。\n",
});

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("wu shun");
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

    damage = COMBAT_D->fight(me, opponent, "wu shun", actions[random(sizeof(actions))], weapon);
}

int
valid_enable(string usage)
{
    return 0;
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("wu shun", 1);
    learn = me->query_learn("wu shun");

    if( !skill ) {
        if( learn >= 1500 ) {
            tell_object(me,
                HIY "你感覺巫順拳法的招式已經融會貫通﹗\n" NOR);
            me->advance_skill("wu shun", 40);
            me->gain_score("martial art", 500);
        }
        return;
    }

    if( (skill < 120) && (skill-39) * (skill-39) * 200 < learn - 1500 ) {
        me->advance_skill("wu shun", 1);
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
        tell_object(me, HIW "由於你巫順拳法的修練有成﹐你的臂力提高了。\n" NOR);
        me->add("str", 1);
    }
}
