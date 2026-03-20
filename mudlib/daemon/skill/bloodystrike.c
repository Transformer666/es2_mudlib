// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
    ([
        "action":       "$N使一招「血手印」﹐雙掌如血焰般拍向$n的$l",
        "dodge":        5,
        "damae":        5,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N施展「赤炎裂空」﹐$w帶著灼熱血氣劈向$n的$l",
        "dodge":        -5,
        "damage":       8,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N怒吼一聲﹐「血雨腥風」的$w如暴雨般砸向$n的$l",
        "dodge":        -10,
        "damage":       10,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N猛然出拳﹐「殺神拳」帶著嗜血殺意轟向$n的$l",
        "dodge":        -15,
        "damae":        15,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N氣勢暴漲﹐「血煞衝天」的$w裹挾血霧衝向$n的$l",
        "dodge":        -5,
        "damage":       10,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N化身修羅﹐「修羅怒擊」的$w帶著滔天殺氣擊向$n的$l",
        "dodge":        10,
        "damae":        7,
        "damage_type":  "瘀傷"
    ]),
});

string *interattack = ({
    "$N雙拳緊握﹐拳頭上泛起一層血紅之色。\n",
});

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("bloody strike");
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

    damage = COMBAT_D->fight(me, opponent, "bloody strike", actions[random(sizeof(actions))], weapon);
}

int
valid_enable(string usage)
{
    return 0;
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("bloody strike", 1);
    learn = me->query_learn("bloody strike");

    if( !skill ) {
        if( learn >= 1500 ) {
            tell_object(me,
                HIY "你感覺血擊的招式已經融會貫通﹗\n" NOR);
            me->advance_skill("bloody strike", 40);
            me->gain_score("martial art", 500);
        }
        return;
    }

    if( (skill < 120) && (skill-39) * (skill-39) * 200 < learn - 1500 ) {
        me->advance_skill("bloody strike", 1);
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
        tell_object(me, HIW "由於你血擊的修練有成﹐你的臂力提高了。\n" NOR);
        me->add("str", 1);
    }
}
