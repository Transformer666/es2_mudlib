// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
    ([
        "action":       "$N持$w往$n的$l刺去",
        "dodge":        5,
        "damae":        5,
        "damage_type":  "刺傷"
    ]),
    ([
        "action":       "$N閃身上前﹐$w朝$n的$l劈去",
        "dodge":        -5,
        "damae":        5,
        "damage_type":  "割傷"
    ]),
    ([
        "action":       "$N欺身而進﹐$w直取$n的$l",
        "dodge":        -10,
        "damage":       10,
        "damage_type":  "刺傷"
    ]),
    ([
        "action":       "$N虛晃一招﹐$w反手攻向$n的$l",
        "dodge":        5,
        "damae":        5,
        "damage_type":  "割傷"
    ]),
    ([
        "action":       "$N忽然暴起﹐$w朝$n的$l猛攻",
        "dodge":        -5,
        "damage":       10,
        "damage_type":  "刺傷"
    ]),
    ([
        "action":       "$N一個側身﹐$w劃向$n的$l",
        "dodge":        10,
        "damae":        5,
        "damage_type":  "割傷"
    ]),
});

string *interattack = ({
    "$N將叉橫在身前﹐虎視眈眈地看著對方。\n",
});

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("fork");
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

    damage = COMBAT_D->fight(me, opponent, "fork", actions[random(sizeof(actions))], weapon);
}

int
valid_enable(string usage)
{
    return 0;
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("fork", 1);
    learn = me->query_learn("fork");

    if( !skill ) {
        if( learn >= 1500 ) {
            tell_object(me,
                HIY "你感覺叉法的招式已經融會貫通﹗\n" NOR);
            me->advance_skill("fork", 40);
            me->gain_score("martial art", 500);
        }
        return;
    }

    if( (skill < 120) && (skill-39) * (skill-39) * 200 < learn - 1500 ) {
        me->advance_skill("fork", 1);
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
        tell_object(me, HIW "由於你叉法的修練有成﹐你的臂力提高了。\n" NOR);
        me->add("str", 1);
    }
}
