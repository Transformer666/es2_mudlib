// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
    ([
        "action":       "$N一式「龍王出海」﹐$w如蛟龍般刺向$n的$l",
        "dodge":        5,
        "damae":        5,
        "damage_type":  "刺傷"
    ]),
    ([
        "action":       "$N施展「三叉鎮海」﹐$w三尖齊出鎖向$n的$l",
        "dodge":        -10,
        "damage":       10,
        "damage_type":  "刺傷"
    ]),
    ([
        "action":       "$N叉勢一沉﹐「海底撈月」的$w自下而上挑向$n的$l",
        "dodge":        -5,
        "damae":        8,
        "damage_type":  "割傷"
    ]),
    ([
        "action":       "$N大喝一聲﹐「翻江倒海」的$w帶著排山之力劈向$n的$l",
        "dodge":        -15,
        "damage":       15,
        "damage_type":  "割傷"
    ]),
    ([
        "action":       "$N橫叉一掃﹐「怒潮拍岸」的$w如怒潮般拍向$n的$l",
        "dodge":        -5,
        "damage":       10,
        "damage_type":  "刺傷"
    ]),
    ([
        "action":       "$N叉勢翻湧﹐「巨浪滔天」的$w裹挾萬鈞之力砸向$n的$l",
        "dodge":        10,
        "damae":        7,
        "damage_type":  "割傷"
    ]),
});

string *interattack = ({
    "$N持叉在手﹐叉法大開大闔﹐威猛無比。\n",
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
