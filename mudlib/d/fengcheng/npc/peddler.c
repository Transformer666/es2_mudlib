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

	set("age", 43);
	set("gender", "female");
	set("long",
		"一個嗓門響亮的北地婦人﹐裹著件半舊的羊皮襖﹐守著自家\n"
		"的小吃攤子﹐見了客人便熱絡地招呼。你可以用 list 看她賣\n"
		"些什麼﹐用 buy 向她買東西。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"攤販扯著嗓子吆喝道﹕熱乎的奶餅乾糧﹐風乾的牛羊肉﹐走過路過莫要錯過哩﹗\n",
		"攤販笑著招呼道﹕客官嚐嚐﹖這北地的吃食扛餓得很﹐趕路最是頂用﹗\n",
		"攤販一面收錢一面數落道﹕這朔風一年到頭颳個不停﹐小本生意難做喲。\n",
	}));
	// 市集小吃攤﹐沿用既有的乾糧吃食物件販售。
	set("merchandise", ([
		"/obj/food/manto" : 60,
		"/obj/food/ricedough" : 50,
		"/obj/food/pork" : 30,
		"/obj/food/mooncake" : 30,
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
