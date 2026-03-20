// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
    ([
        "action":       "$N使出「火辣連環」﹐雙爪連環抓向$n的$l",
        "dodge":        -5,
        "damae":        9,
        "damage_type":  "割傷"
    ]),
    ([
        "action":       "$N猛施「烈焰抓心」﹐灼熱的爪勁直取$n的$l",
        "dodge":        -15,
        "damage":       15,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N翻手使出「灼爪焚天」﹐爪風炙熱地掃向$n的$l",
        "dodge":        -10,
        "damae":        11,
        "damage_type":  "割傷"
    ]),
    ([
        "action":       "$N冷笑一聲施展「辣手摧花」﹐毒辣地攻向$n的$l",
        "dodge":        5,
        "damage":       8,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N雙爪齊出使出「烈火燎原」﹐爪影鋪天蓋地襲向$n的$l",
        "dodge":        -10,
        "damae":        13,
        "damage_type":  "割傷"
    ]),
    ([
        "action":       "$N陰狠地使出「毒辣鬼爪」﹐詭異的爪勁攻向$n的$l",
        "dodge":        10,
        "damage":       6,
        "damage_type":  "瘀傷"
    ]),
});

string *interattack = ({
    "$N雙手翻飛﹐辣爪的爪勢又快又狠。\n",
});

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("spicyclaw");
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

    damage = COMBAT_D->fight(me, opponent, "spicyclaw", actions[random(sizeof(actions))], weapon);
}

int
valid_enable(string usage)
{
    return 0;
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("spicyclaw", 1);
    learn = me->query_learn("spicyclaw");

    if( !skill ) {
        if( learn >= 1500 ) {
            tell_object(me,
                HIY "你感覺辣爪功的招式已經融會貫通﹗\n" NOR);
            me->advance_skill("spicyclaw", 40);
            me->gain_score("martial art", 500);
        }
        return;
    }

    if( (skill < 120) && (skill-39) * (skill-39) * 200 < learn - 1500 ) {
        me->advance_skill("spicyclaw", 1);
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
        tell_object(me, HIW "由於你辣爪功的修練有成﹐你的敏捷提高了。\n" NOR);
        me->add("dex", 1);
    }
}
