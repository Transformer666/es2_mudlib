// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("force");
    setup();
}

int valid_learn(object me) { return 1; }

int valid_enable(string usage)
{
    return usage == "force";
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("force", 1);
    learn = me->query_learn("force");

    if( !skill ) {
	if( learn >= 1000 ) {
	    tell_object(me,
		HIY "你感覺體內真氣流轉不息﹐基礎內功已經練成了﹗\n" NOR);
	    me->advance_skill("force", 30);
	    me->gain_score("martial art", 300);
	}
	return;
    }

    if( (skill < 120) && (skill-29) * (skill-29) * 200 < learn - 1000 ) {
	me->advance_skill("force", 1);
	me->gain_score("martial art", (skill+1) * 8);
	if( skill >= 50 )
	    me->gain_score("martial mastery", (skill-40) * 8);
    }
}

void skill_advanced(object me, string sk)
{
    int level;

    level = me->query_skill(sk, 1);
    if( me->query_stat_maximum("gin") < level * 12 )
	me->advance_stat("gin", 5);
    if( me->query_stat_maximum("kee") < level * 10 )
	me->advance_stat("kee", 4);
    if( me->query_stat_maximum("sen") < level * 12 )
	me->advance_stat("sen", 5);

    if( level % 10 == 9 && me->query_attr("con") < level / 4 ) {
	tell_object(me, HIW "由於你的內功修練有成﹐你的體質改善了。\n" NOR);
	me->add("con", 2);
    }
}

int inflict_damage(int strength, object victim)
{
    int damage;

    damage = 1 + strength / 8000 + random(strength / 8000);
    damage -= victim->resist_damage(damage, this_object());
    return damage > 0 ? victim->receive_damage(damage, this_object()) : 0;
}
