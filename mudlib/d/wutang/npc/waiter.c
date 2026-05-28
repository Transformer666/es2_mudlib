// waiter.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("店小二", ({ "waiter", "wutang_inn_waiter" }) );
	set_race("human");
	set_class("commoner");
	set_level(2);

	set("age", 19);
	set("gender", "male");
	set("long",
		"一個機靈的小夥計﹐肩上搭著一條抹布﹐在桌椅之間穿梭招呼。你\n"
		"可以用 list 看可以點什麼﹐用 buy 跟店小二點菜。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"店小二一邊抹桌子﹐一邊哼著不成調的小曲兒。\n",
		"店小二吆喝道﹕客官想吃點什麼﹖熱乎的饅頭剛出籠哩﹗\n",
	}));
	set("merchandise", ([
		"/obj/food/manto" : 50,
		"/obj/food/dumpling" : 50,
		"/obj/food/pork" : 30,
		"/obj/food/mooncake" : 20,
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
	do_chat("店小二縮了縮脖子﹐說道﹕客官別動手﹐小的可不經打。\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
