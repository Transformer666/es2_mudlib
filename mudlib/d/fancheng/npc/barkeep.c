// barkeep.c -- 望安客棧的酒保（F_VENDOR 供應乾糧吃食）

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("酒保", ({ "barkeep", "fancheng_inn_barkeep" }) );
	set_race("human");
	set_class("commoner");
	set_level(2);

	set("age", 22);
	set("gender", "male");
	set("long",
		"一個手腳麻利的酒保﹐肩上搭著條濕漉漉的抹布﹐在桌椅之\n"
		"間穿梭招呼﹐替客人篩酒添菜。你可以用 list 看可以點什麼﹐\n"
		"用 buy 跟酒保點菜。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"酒保脆生生地吆喝道﹕客官您點什麼﹖小店的海鮮乾糧管夠管飽﹗\n",
		"酒保一面替客人篩著熱酒﹐一面哼著海邊時興的漁歌小調兒。\n",
	}));
	// 客棧前廳供應乾糧吃食﹐沿用既有的食物物件販售。
	set("merchandise", ([
		"/obj/food/manto" : 50,
		"/obj/food/pork" : 40,
		"/obj/food/dumpling" : 50,
		"/obj/food/mooncake" : 30,
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
	do_chat("酒保縮著脖子賠笑道﹕客官息怒﹐小的這就給您換桌好的﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
