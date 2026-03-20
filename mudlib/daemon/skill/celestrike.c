// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
    ([
        "action":       "$N一式「天罰之拳」﹐$w帶著天威轟向$n的$l",
        "dodge":        5,
        "damae":        5,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N施展「雷霆萬鈞」﹐$w如雷霆般劈向$n的$l",
        "dodge":        -5,
        "damage":       8,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N躍起怒擊﹐「九天隕落」的$w如隕石般砸向$n的$l",
        "dodge":        -15,
        "damage":       15,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N怒目圓睜﹐「天威震怒」的$w裹挾狂風擊向$n的$l",
        "dodge":        -10,
        "damae":        10,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N凝聚星力﹐「星辰墜擊」的$w帶著星芒砸向$n的$l",
        "dodge":        -5,
        "damae":        10,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N集天地之力﹐「天崩地裂」的$w如山崩般壓向$n的$l",
        "dodge":        10,
        "damage":       7,
        "damage_type":  "瘀傷"
    ]),
});

string *interattack = ({
    "$N凝聚天地之氣﹐天擊的拳勢如雷霆般蓄勢待發。\n",
});

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("celestrike");
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

    damage = COMBAT_D->fight(me, opponent, "celestrike", actions[random(sizeof(actions))], weapon);
}

int
valid_enable(string usage)
{
    return 0;
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("celestrike", 1);
    learn = me->query_learn("celestrike");

    if( !skill ) {
        if( learn >= 1500 ) {
            tell_object(me,
                HIY "你感覺天擊的招式已經融會貫通﹗\n" NOR);
            me->advance_skill("celestrike", 40);
            me->gain_score("martial art", 500);
        }
        return;
    }

    if( (skill < 120) && (skill-39) * (skill-39) * 200 < learn - 1500 ) {
        me->advance_skill("celestrike", 1);
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
        tell_object(me, HIW "由於你天擊的修練有成﹐你的臂力提高了。\n" NOR);
        me->add("str", 1);
    }
}
