// vim: syntax=lpc
// mysterrier.c - 步玄七訣（閃避/身法技能）

#include <ansi.h>

inherit SKILL;

string *dodge_msg = ({
    "$n身影一轉，輕易地避開了這一招。\n",
    "$n身法飄忽，左一點，右一頓，早已閃在一旁。\n",
    "但是$n身影一側，在間不容髮之際從容地避開了這一招。\n",
    "$n身形陡然拔高，使$N的攻勢盡數落空。\n",
    "$n右足一點，身影向左滑開數尺，避了開去。\n",
});

private void
create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("mysterrier");
    setup();
}

int valid_enable(string usage)
{
    return (usage == "dodge") || (usage == "move");
}

int valid_learn(object me)
{
    if( me->query_skill_mapped("force") != "mystforce" )
	return notify_fail("步玄七訣必須配合步玄心法使用。\n");
    if( me->query_skill("music") < me->query_skill("mysterrier") / 2 )
	return notify_fail("你的音律之學修為不夠，無法領悟更高深的步玄七訣。\n");

    return 1;
}

string query_dodge_msg(string limb)
{
    return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
    if( (int)me->query("kee") < 20
    ||  (int)me->query("sen") < 20 )
	return notify_fail("你的氣或神不夠，不能練步玄七訣。\n");
    me->receive_damage("kee", 20);
    me->receive_damage("sen", 20);
    return 1;
}

string perform_action_file(string action)
{
    return CLASS_D("scholar") + "/mysterrier/" + action;
}

void skill_improved(object me, string sk)
{
    int skill, learn;

    skill = me->query_skill("mysterrier", 1);
    learn = me->query_learn("mysterrier");

    if( !skill ) {
	if( learn >= 500 ) {
	    tell_object(me,
		HIY "你覺得自己的身法靈動了許多，步玄七訣的技巧已有所領悟！\n" NOR);
	    me->advance_skill("mysterrier", 1);
	}
	return;
    }

    if( (skill < 120) && (skill) * (skill) * 100 < learn - 500 ) {
	me->advance_skill("mysterrier", 1);
	me->gain_score("martial art", (skill+1) * 5);
    }
}

void skill_advanced(object me, string sk)
{
    int level;

    level = me->query_skill(sk, 1);
    if( level % 10 == 9 && me->query_attr("dex") < level / 3 ) {
	tell_object(me, HIW "由於你勤練步玄七訣，你的敏捷提高了。\n" NOR);
	me->add("dex", 1);
    }
}
