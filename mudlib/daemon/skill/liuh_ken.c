// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
    ([
        "action":       "$N使一招「龍拳」﹐拳如蛟龍出海般擊向$n的$l",
        "dodge":        -10,
        "damae":        10,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N施展「虎拳」﹐虎虎生風地砸向$n的$l",
        "dodge":        -5,
        "damage":       12,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N翩然使出「鶴拳」﹐單腳獨立啄向$n的$l",
        "dodge":        5,
        "damae":        8,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N身形扭動使出「蛇拳」﹐詭異地纏向$n的$l",
        "dodge":        10,
        "damae":        6,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N跳躍騰挪使出「猴拳」﹐靈巧地攻向$n的$l",
        "dodge":        -5,
        "damage":       10,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N雙臂揮動使出「螳螂拳」﹐連環快攻$n的$l",
        "dodge":        -15,
        "damae":        15,
        "damage_type":  "瘀傷"
    ]),
});

string *interattack = ({
    "$N擺出六拳的架式﹐拳風凌厲。\n",
});

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("liuh ken");
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

    damage = COMBAT_D->fight(me, opponent, "liuh ken", actions[random(sizeof(actions))], weapon);
}

int
valid_enable(string usage)
{
    return 0;
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("liuh ken", 1);
    learn = me->query_learn("liuh ken");

    if( !skill ) {
        if( learn >= 1500 ) {
            tell_object(me,
                HIY "你感覺六拳的招式已經融會貫通﹗\n" NOR);
            me->advance_skill("liuh ken", 40);
            me->gain_score("martial art", 500);
        }
        return;
    }

    if( (skill < 120) && (skill-39) * (skill-39) * 200 < learn - 1500 ) {
        me->advance_skill("liuh ken", 1);
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
        tell_object(me, HIW "由於你六拳的修練有成﹐你的臂力提高了。\n" NOR);
        me->add("str", 1);
    }
}
