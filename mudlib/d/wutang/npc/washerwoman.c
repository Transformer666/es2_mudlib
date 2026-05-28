// washerwoman.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("浣衣婦", ({ "washerwoman", "woman" }) );
	set_race("human");
	set_class("commoner");
	set_level(2);

	set("age", 32);
	set("gender", "female");
	set("long",
		"一個衣著樸素的婦人﹐挽著袖子蹲在井邊浣洗衣裳﹐木杵起落﹐手\n"
		"腳十分俐落。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		"浣衣婦用木杵捶打著衣物﹐發出一陣陣悶響。\n",
		"浣衣婦頭也不抬地說道﹕這位客官﹐打水請等我洗完這桶。\n",
		"浣衣婦絞著衣裳說道﹕這口老井的水又清又甜﹐全鎮就數它最好。\n",
	}));
	setup();
	carry_object("/obj/area/obj/cloth")->wear();
	carry_money("coin", 8);
}

int accept_fight()
{
	do_chat("浣衣婦嚇得花容失色﹐連聲道﹕別﹗別﹗我一個婦道人家 ...\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
