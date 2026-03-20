// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
    ([
        "action":       "$N使出「鷹爪擒拿」﹐五指如鉤扣向$n的$l",
        "dodge":        -10,
        "damae":        10,
        "damage_type":  "割傷"
    ]),
    ([
        "action":       "$N猛然施展「虎爪裂肉」﹐利爪撕向$n的$l",
        "dodge":        -15,
        "damage":       14,
        "damage_type":  "割傷"
    ]),
    ([
        "action":       "$N伸手使出「龍爪探珠」﹐直探$n的$l",
        "dodge":        -5,
        "damae":        8,
        "damage_type":  "割傷"
    ]),
    ([
        "action":       "$N翻手使出「鳳爪穿林」﹐爪影紛飛刺向$n的$l",
        "dodge":        5,
        "damae":        7,
        "damage_type":  "割傷"
    ]),
    ([
        "action":       "$N大喝一聲使出「熊掌碎骨」﹐巨力拍向$n的$l",
        "dodge":        -10,
        "damage":       13,
        "damage_type":  "割傷"
    ]),
    ([
        "action":       "$N身形一晃使出「蛇爪纏絲」﹐陰柔地纏向$n的$l",
        "dodge":        10,
        "damae":        5,
        "damage_type":  "割傷"
    ]),
});

string *interattack = ({
    "$N十指微曲如鉤﹐抓法的爪勢凶狠無比。\n",
});

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("scratching");
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

    damage = COMBAT_D->fight(me, opponent, "scratching", actions[random(sizeof(actions))], weapon);
}

int
valid_enable(string usage)
{
    return 0;
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("scratching", 1);
    learn = me->query_learn("scratching");

    if( !skill ) {
        if( learn >= 1500 ) {
            tell_object(me,
                HIY "你感覺爪法的招式已經融會貫通﹗\n" NOR);
            me->advance_skill("scratching", 40);
            me->gain_score("martial art", 500);
        }
        return;
    }

    if( (skill < 120) && (skill-39) * (skill-39) * 200 < learn - 1500 ) {
        me->advance_skill("scratching", 1);
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
        tell_object(me, HIW "由於你爪法的修練有成﹐你的敏捷提高了。\n" NOR);
        me->add("dex", 1);
    }
}
