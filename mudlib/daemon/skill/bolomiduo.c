// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
    ([
        "action":       "$N一式「般若掌」﹐$w帶著佛光拍向$n的$l",
        "dodge":        5,
        "damae":        5,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N施展「菩提無相」﹐$w虛實莫辨地攻向$n的$l",
        "dodge":        10,
        "damage":       7,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N運起「金剛指」﹐$w如金剛怒目般點向$n的$l",
        "dodge":        -10,
        "damage":       10,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N大喝一聲﹐「如來神掌」的$w帶著萬鈞之力壓向$n的$l",
        "dodge":        -15,
        "damae":        15,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N悲憫低語﹐「大悲心法」的$w柔中帶剛擊向$n的$l",
        "dodge":        -5,
        "damae":        8,
        "damage_type":  "瘀傷"
    ]),
    ([
        "action":       "$N雙掌結印﹐「摩訶印」的$w帶著梵音震向$n的$l",
        "dodge":        -5,
        "damage":       10,
        "damage_type":  "瘀傷"
    ]),
});

string *interattack = ({
    "$N雙掌合十﹐口中低誦般若心經。\n",
});

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("bolomiduo");
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

    damage = COMBAT_D->fight(me, opponent, "bolomiduo", actions[random(sizeof(actions))], weapon);
}

int
valid_enable(string usage)
{
    return 0;
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("bolomiduo", 1);
    learn = me->query_learn("bolomiduo");

    if( !skill ) {
        if( learn >= 1500 ) {
            tell_object(me,
                HIY "你感覺般若掌的招式已經融會貫通﹗\n" NOR);
            me->advance_skill("bolomiduo", 40);
            me->gain_score("martial art", 500);
        }
        return;
    }

    if( (skill < 120) && (skill-39) * (skill-39) * 200 < learn - 1500 ) {
        me->advance_skill("bolomiduo", 1);
        me->gain_score("martial art", (skill+1) * 10);
        if( skill >= 50 )
            me->gain_score("martial mastery", (skill-40) * 10);
    }
}

void skill_advanced(object me, string sk)
{
    int level;

    level = me->query_skill(sk, 1);
    if( level % 10 == 9 && me->query_attr("wis") < level / 3 ) {
        tell_object(me, HIW "由於你般若掌的修練有成﹐你的悟性提高了。\n" NOR);
        me->add("wis", 1);
    }
}
