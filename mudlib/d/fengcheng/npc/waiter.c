// waiter.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("店小二", ({ "waiter", "fengcheng_inn_waiter" }) );
	set_race("human");
	set_class("commoner");
	set_level(2);

	set("age", 20);
	set("gender", "male");
	set("long",
		"一個眼明手快的小夥計﹐肩上搭著一條抹布﹐在桌椅之間穿\n"
		"梭招呼﹐替客人添炭續茶。你可以用 list 看可以點什麼﹐用\n"
		"buy 跟店小二點菜。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"店小二脆生生地吆喝道﹕客官您點什麼﹖小店的牛羊乾糧管夠管飽﹗\n",
		"店小二一面替客人的火盆添著炭﹐一面哼著時興的小調兒。\n",
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
	do_chat("店小二縮著脖子賠笑道﹕客官息怒﹐小的這就給您換桌好的﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
