// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
    ([
        "action":       "$N一式「天師降魔」﹐$w帶著道家正氣擊向$n的$l",
        "dodge":        5,
        "damae":        5,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N施展「五雷正法拳」﹐$w裹挾雷電之力劈向$n的$l",
        "dodge":        -10,
        "damage":       12,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N掌法一變﹐「紫微掌」的$w帶著紫氣拍向$n的$l",
        "dodge":        -5,
        "damae":        8,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N拳勢如星辰運轉﹐「北斗拳」的$w直取$n的$l",
        "dodge":        -15,
        "damage":       15,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N運起天罡之氣﹐「天罡破邪」的$w正氣凜然地擊向$n的$l",
        "dodge":        -5,
        "damage":       10,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N收勢歸元﹐「太極歸一」的$w綿綿不絕地壓向$n的$l",
        "dodge":        10,
        "damae":        7,
        "damage_type":  "瘀傷"
    ]),
});

string *interattack = ({
    "$N擺出天師拳法的起手式﹐拳上隱隱泛出道家真氣。\n",
});

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("ts fist");
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

    damage = COMBAT_D->fight(me, opponent, "ts fist", actions[random(sizeof(actions))], weapon);
}

int
valid_enable(string usage)
{
    return 0;
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("ts fist", 1);
    learn = me->query_learn("ts fist");

    if( !skill ) {
        if( learn >= 1500 ) {
            tell_object(me,
                HIY "你感覺天山拳法的招式已經融會貫通﹗\n" NOR);
            me->advance_skill("ts fist", 40);
            me->gain_score("martial art", 500);
        }
        return;
    }

    if( (skill < 120) && (skill-39) * (skill-39) * 200 < learn - 1500 ) {
        me->advance_skill("ts fist", 1);
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
        tell_object(me, HIW "由於你天山拳法的修練有成﹐你的臂力提高了。\n" NOR);
        me->add("str", 1);
    }
}
