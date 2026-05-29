// barkeep.c -- 羅城客棧的酒保（F_VENDOR 供應乾糧吃食）

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("店小二", ({ "luocheng_inn_barkeep", "barkeep", "xiaoer" }) );
	set_race("human");
	set_class("commoner");
	set_level(2);

	set("age", 21);
	set("gender", "male");
	set("long",
		"一個手腳麻利的店小二﹐肩上搭著條乾淨的手巾﹐在桌椅之\n"
		"間穿梭招呼﹐替客人篩茶添點。你可以用 list 看可以點什麼﹐\n"
		"用 buy 跟店小二點吃食。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"店小二脆生生地吆喝道﹕老爺您點什麼﹖小店的細點乾糧樣樣齊備﹗\n",
		"店小二一面替客人續著熱茶﹐一面殷勤地抹著鄰桌的桌面。\n",
	}));
	// 客棧前廳供應乾糧吃食﹐沿用既有的食物物件販售。
	set("merchandise", ([
		"/obj/food/manto" : 50,
		"/obj/food/dumpling" : 50,
		"/obj/food/mooncake" : 30,
		"/obj/food/pork" : 40,
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
	do_chat("店小二縮著脖子賠笑道﹕老爺息怒﹐小的這就給您換桌好的﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
