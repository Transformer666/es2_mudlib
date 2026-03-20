// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
    ([
        "action":       "$N一式「雁翎鉤影」﹐$w如雁翎般輕巧地勾向$n的$l",
        "dodge":        5,
        "damae":        5,
        "damage_type":  "割傷"
    ]),
    ([
        "action":       "$N施展「勾魂奪魄」﹐$w帶著攝人寒光鉤向$n的$l",
        "dodge":        -10,
        "damage":       10,
        "damage_type":  "割傷"
    ]),
    ([
        "action":       "$N鉤法一轉﹐「回風拂柳」的$w柔中帶剛劃向$n的$l",
        "dodge":        10,
        "damae":        7,
        "damage_type":  "刺傷"
    ]),
    ([
        "action":       "$N猛然出鉤﹐「鉤鐮斷腕」的$w狠辣地切向$n的$l",
        "dodge":        -15,
        "damage":       15,
        "damage_type":  "割傷"
    ]),
    ([
        "action":       "$N雙鉤連環﹐「盤蛇七探」的$w如毒蛇般纏向$n的$l",
        "dodge":        -5,
        "damae":        8,
        "damage_type":  "刺傷"
    ]),
    ([
        "action":       "$N虛晃一鉤﹐「暗渡陳倉」的$w從意想不到的角度刺向$n的$l",
        "dodge":        -5,
        "damage":       10,
        "damage_type":  "割傷"
    ]),
});

string *interattack = ({
    "$N手持雙鉤﹐鉤義的招式詭譎多變。\n",
});

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("gouyee");
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

    damage = COMBAT_D->fight(me, opponent, "gouyee", actions[random(sizeof(actions))], weapon);
}

int
valid_enable(string usage)
{
    return 0;
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("gouyee", 1);
    learn = me->query_learn("gouyee");

    if( !skill ) {
        if( learn >= 1500 ) {
            tell_object(me,
                HIY "你感覺鉤弋功的招式已經融會貫通﹗\n" NOR);
            me->advance_skill("gouyee", 40);
            me->gain_score("martial art", 500);
        }
        return;
    }

    if( (skill < 120) && (skill-39) * (skill-39) * 200 < learn - 1500 ) {
        me->advance_skill("gouyee", 1);
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
        tell_object(me, HIW "由於你鉤弋功的修練有成﹐你的敏捷提高了。\n" NOR);
        me->add("dex", 1);
    }
}
