// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
    ([
        "action":       "$N使出「狂風驟雨」﹐拳腳如暴雨般傾瀉向$n的$l",
        "dodge":        -10,
        "damae":        11,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N旋身施展「暴風旋舞」﹐旋風般掃向$n的$l",
        "dodge":        -15,
        "damage":       14,
        "damage_type":  "割傷"
    ]),
    ([
        "action":       "$N凌空使出「雷電交加」﹐迅雷不及掩耳地劈向$n的$l",
        "dodge":        -5,
        "damae":        9,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N狂舞使出「颶風裂空」﹐撕裂般的勁風攻向$n的$l",
        "dodge":        -10,
        "damage":       13,
        "damage_type":  "割傷"
    ]),
    ([
        "action":       "$N忽然靜止使出「風暴之眼」﹐瞬間爆發擊向$n的$l",
        "dodge":        10,
        "damae":        6,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N翻轉騰挪使出「天旋地轉」﹐令人目眩地攻向$n的$l",
        "dodge":        5,
        "damage":       8,
        "damage_type":  "割傷"
    ]),
});

string *interattack = ({
    "$N舞動身形﹐風暴舞帶起一陣狂風。\n",
});

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("stormdance");
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

    damage = COMBAT_D->fight(me, opponent, "stormdance", actions[random(sizeof(actions))], weapon);
}

int
valid_enable(string usage)
{
    return 0;
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("stormdance", 1);
    learn = me->query_learn("stormdance");

    if( !skill ) {
        if( learn >= 1500 ) {
            tell_object(me,
                HIY "你感覺暴風舞的招式已經融會貫通﹗\n" NOR);
            me->advance_skill("stormdance", 40);
            me->gain_score("martial art", 500);
        }
        return;
    }

    if( (skill < 120) && (skill-39) * (skill-39) * 200 < learn - 1500 ) {
        me->advance_skill("stormdance", 1);
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
        tell_object(me, HIW "由於你暴風舞的修練有成﹐你的敏捷提高了。\n" NOR);
        me->add("dex", 1);
    }
}
