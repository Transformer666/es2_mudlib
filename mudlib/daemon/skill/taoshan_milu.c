// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

void create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("taoshan milu");
}

int valid_enable(string usage)
{
    return usage == "force";
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("taoshan milu", 1);
    learn = me->query_learn("taoshan milu", 1);

    if( !skill ) {
	if( learn >= 2500 ) {
	    tell_object(me,
		HIY "你感覺靈台一片清明﹐桃山密籙的玄功已經練成了﹗\n" NOR);
	    me->advance_skill("taoshan milu", 40);
	    me->gain_score("martial art", 800);
	}
	return;
    }

    if( (skill < 150) && (skill-39) * (skill-39) * 250 < learn - 2500 ) {
	me->advance_skill("taoshan milu", 1);
	me->gain_score("martial art", (skill+1) * 15);
	if( skill >= 50 )
	    me->gain_score("martial mastery", (skill-40) * 15);
    }
}

void skill_advanced(object me, string sk)
{
    int level;

    level = me->query_skill(sk, 1);
    if( me->query_stat_maximum("gin") < level * 16 )
	me->advance_stat("gin", 7);
    if( me->query_stat_maximum("kee") < level * 14 )
	me->advance_stat("kee", 6);
    if( me->query_stat_maximum("sen") < level * 18 )
	me->advance_stat("sen", 8);
}

int do_exercise(object me)
{
    if( me->query_stat("gin") < 15
    ||  me->query_stat("kee") < 15
    ||  me->query_stat("sen") < 15 ) {
	tell_object(me, "你覺得神困力乏﹐沒有辦法繼續練功了。\n");
	me->interrupt_me(me, "exhausted");
	return 1;
    }
    me->consume_stat("gin", 15);
    me->consume_stat("kee", 15);
    me->consume_stat("sen", 15);

    if( random(me->query_attr("spi") + me->query_attr("wis") + me->query_skill("force", 1)) > 25 ) {
	me->damage_stat("gin", 2);
	me->damage_stat("kee", 1);
	me->damage_stat("sen", 2);
	me->improve_skill("taoshan milu", random(me->query_attr("spi")/8) + 1);
	me->improve_skill("force", random(me->query_attr("wis")/8) + 1);
    }
    return 1;
}

int halt_exercise(object me, object owner, object from, string how)
{
    return 1;
}

varargs int
exert_function(object me, string func, object target)
{
    switch(func) {
    case "taoshan milu":
	message_vision(HIY "$N閉目凝神﹐修煉桃山密籙的玄功。\n" NOR,
	    me);
	me->start_busy((: do_exercise, me :), (: halt_exercise, me :));
	return 1;
    default:
	return notify_fail("桃山密籙沒有這種功能。\n");
    }
}
