// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
    ([
        "action":       "$N使出「柔情似水」﹐指尖輕柔地點向$n的$l",
        "dodge":        10,
        "damae":        6,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N施展「纖指點穴」﹐纖指疾點$n的$l",
        "dodge":        -5,
        "damage":       10,
        "damage_type":  "刺傷"
    ]),
    ([
        "action":       "$N翩然使出「蘭花拂穴」﹐指如蘭花般拂向$n的$l",
        "dodge":        5,
        "damae":        8,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N使出「玉指纏絲」﹐指力纏繞攻向$n的$l",
        "dodge":        -10,
        "damage":       12,
        "damage_type":  "刺傷"
    ]),
    ([
        "action":       "$N輕彈玉指使出「輕指彈夢」﹐指風飄渺地擊向$n的$l",
        "dodge":        -5,
        "damae":        9,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N忽然指力一變使出「柔中帶剛」﹐剛猛地戳向$n的$l",
        "dodge":        -15,
        "damage":       14,
        "damage_type":  "刺傷"
    ]),
});

string *interattack = ({
    "$N手指纖纖﹐柔指功的指法看似柔弱實則暗藏殺機。\n",
});

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("tenderzhi");
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

    damage = COMBAT_D->fight(me, opponent, "tenderzhi", actions[random(sizeof(actions))], weapon);
}

int
valid_enable(string usage)
{
    return 0;
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("tenderzhi", 1);
    learn = me->query_learn("tenderzhi");

    if( !skill ) {
        if( learn >= 1500 ) {
            tell_object(me,
                HIY "你感覺柔指功的招式已經融會貫通﹗\n" NOR);
            me->advance_skill("tenderzhi", 40);
            me->gain_score("martial art", 500);
        }
        return;
    }

    if( (skill < 120) && (skill-39) * (skill-39) * 200 < learn - 1500 ) {
        me->advance_skill("tenderzhi", 1);
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
        tell_object(me, HIW "由於你柔指功的修練有成﹐你的敏捷提高了。\n" NOR);
        me->add("dex", 1);
    }
}
