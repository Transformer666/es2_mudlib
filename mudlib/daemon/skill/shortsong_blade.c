// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
    ([
        "action":       "$N低吟一聲﹐使出「短歌行」﹐$w如行雲般劃向$n的$l",
        "dodge":        5,
        "damae":        5,
        "damage_type":  "割傷"
    ]),
    ([
        "action":       "$N一式「長河落日」﹐$w帶著蒼涼之意劈向$n的$l",
        "dodge":        -10,
        "damage":       12,
        "damage_type":  "斲傷"
    ]),
    ([
        "action":       "$N刀光一閃﹐「斷雲殘照」﹐$w直取$n的$l",
        "dodge":        -5,
        "damae":        8,
        "damage_type":  "割傷"
    ]),
    ([
        "action":       "$N悲歌長嘯﹐使出「秋風辭」﹐$w橫掃$n的$l",
        "dodge":        -15,
        "damage":       15,
        "damage_type":  "割傷"
    ]),
    ([
        "action":       "$N刀勢驟變﹐一招「慷慨悲歌」﹐$w猛攻$n的$l",
        "dodge":        -5,
        "damage":       10,
        "damage_type":  "斲傷"
    ]),
    ([
        "action":       "$N決然出刀﹐「壯士斷腕」﹐$w不顧一切砍向$n的$l",
        "dodge":        10,
        "damae":        7,
        "damage_type":  "割傷"
    ]),
});

string *interattack = ({
    "$N持刀在手﹐短歌刀法如吟詩般行雲流水。\n",
});

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("shortsong blade");
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

    damage = COMBAT_D->fight(me, opponent, "shortsong blade", actions[random(sizeof(actions))], weapon);
}

int
valid_enable(string usage)
{
    return 0;
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("shortsong blade", 1);
    learn = me->query_learn("shortsong blade");

    if( !skill ) {
        if( learn >= 1500 ) {
            tell_object(me,
                HIY "你感覺短松刀法的招式已經融會貫通﹗\n" NOR);
            me->advance_skill("shortsong blade", 40);
            me->gain_score("martial art", 500);
        }
        return;
    }

    if( (skill < 120) && (skill-39) * (skill-39) * 200 < learn - 1500 ) {
        me->advance_skill("shortsong blade", 1);
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
        tell_object(me, HIW "由於你短松刀法的修練有成﹐你的臂力提高了。\n" NOR);
        me->add("str", 1);
    }
}
