// peddler.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("攤販", ({ "peddler", "vendor" }) );
	set_race("human");
	set_class("commoner");
	set_level(3);

	set("age", 41);
	set("gender", "female");
	set("long",
		"一個嗓門響亮的婦人﹐守著自家的小吃攤子﹐見了客人便熱絡\n"
		"地招呼。你可以用 list 看她賣些什麼﹐用 buy 向她買東西。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"攤販扯著嗓子吆喝道﹕剛出鍋的熱乎吃食﹐走過路過莫要錯過哩﹗\n",
		"攤販笑著招呼道﹕客官嚐嚐﹖我這手藝在這市集上可是出了名的﹗\n",
		"攤販一面收錢一面數落道﹕這年頭米麵都漲了價﹐小本生意難做喲。\n",
	}));
	// 市集小吃攤﹐沿用既有的乾糧吃食物件販售。
	set("merchandise", ([
		"/obj/food/manto" : 60,
		"/obj/food/ricedough" : 50,
		"/obj/food/mooncake" : 30,
		"/obj/food/pork" : 20,
	]));

	setup();
	carry_money("coin", 120);
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
}

int accept_fight(object ob)
{
	do_chat("攤販雙手叉腰﹐高聲嚷道﹕光天化日的﹐你想幹什麼﹖來人哪﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
