// caiyaofu.c -- 百藥谷采藥小徑上采藥的婦人（F_VILLAGER﹐純氣氛、非戰鬥）。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("采藥婦", ({ "caiyaofu", "herb woman", "woman" }) );
	set("nickname", "采藥婦");
	set_race("human");
	set_class("commoner");
	set_level(6);

	set("age", 38);
	set("gender", "female");
	set("long",
		"一個四十上下的采藥婦人﹐裹著青布頭巾﹐背著個半人高的竹\n"
		"簍﹐腰間別著把採藥的小鏟。她手腳俐落﹐攀崖鑽隙如履平地﹐\n"
		"一雙手認藥摘藥又快又準﹐想是進這谷采了多年的藥。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"采藥婦踮腳攀著崖壁﹐小心地將一叢紫花野藥連根掘下﹐抖落泥土收進竹簍。\n",
		"采藥婦直起腰捶了捶背﹐笑道﹕這崖上的石斛金貴﹐城裡的藥鋪搶著要﹐累是累些﹐換得銅錢哩。\n",
		"采藥婦一面採藥﹐一面道﹕客官小心腳下﹐這小徑滑得很﹐莫摔著了。\n",
	}));

	setup();
}

int accept_fight(object ob)
{
	do_chat("采藥婦慌忙護住竹簍往崖邊退﹕這位客官﹐使不得使不得呀﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
