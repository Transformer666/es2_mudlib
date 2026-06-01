// barkeep.c -- 天仁客棧的酒保（F_VENDOR 供應乾糧吃食）

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("酒保", ({ "barkeep", "zhaoyin_inn_barkeep" }) );
	set_race("human");
	set_class("commoner");
	set_level(2);

	set("age", 19);
	set("gender", "male");
	set("long",
		"一個憨厚的鄉下少年酒保﹐肩上搭著條洗得發白的抹布﹐在\n"
		"桌椅間勤快地穿梭招呼﹐替客人篩茶添飯。你可以用 list 看可\n"
		"以點什麼﹐用 buy 跟酒保點菜。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"酒保憨憨地招呼道﹕客官您點什麼﹖小店的茶飯吃食﹐管夠管飽﹗\n",
		"酒保一面替客人篩著熱茶﹐一面哼著鄉間的山歌小調兒。\n",
	}));
	// 客棧前廳供應乾糧吃食﹐沿用既有的食物物件販售。
	set("merchandise", ([
		"/obj/food/manto" : 45,
		"/obj/food/ricedough" : 40,
		"/obj/food/dumpling" : 45,
	]));

	setup();
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
}

int accept_fight(object ob)
{
	do_chat("酒保嚇得縮起脖子賠笑﹕客官息怒﹐小的這就給您換桌好的﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
