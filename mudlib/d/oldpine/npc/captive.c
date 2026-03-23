// captive.c - 被土匪綁架的行商
// Quest: bandit_hostage_rescue

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("行商", ({"captive", "merchant", "trader"}));
	set_attr("str", 12);
	set_attr("con", 14);
	set_attr("dex", 10);
	set_race("human");
	set_class("commoner");
	set_level(5);

	set("age", 35);
	set("gender", "male");
	set("long",
		"一個中年行商被五花大綁地丟在角落裡﹐嘴裡塞著破布﹐臉上滿\n"
		"是烏青和血跡。他睜著充滿恐懼的眼睛看著你﹐不住地嗚嗚叫著﹐\n"
		"似乎想要說些什麼。\n");

	setup();
}

void relay_say(object me, string msg)
{
	if( is_fighting() || is_chatting() ) return;

	if( query_temp("untied") ) {
		if( strsrch(msg, "土匪") >= 0 || strsrch(msg, "bandit") >= 0 ) {
			do_chat(({
				"行商哆嗦著說道﹕我從康平過來﹐在松林裡被這幫土匪截住了。\n",
				"行商說道﹕他們搶走了我所有的貨物﹐還把我綁在這裡 ...\n",
				"行商說道﹕本來以為這次死定了﹐沒想到遇到恩人你。\n",
			}));
			return;
		}
	}
}
