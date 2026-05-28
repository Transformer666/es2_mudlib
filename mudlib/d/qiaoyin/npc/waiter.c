// waiter.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("店小二", ({ "waiter", "qiaoyin_inn_waiter" }) );
	set_race("human");
	set_class("commoner");
	set_level(2);

	set("age", 21);
	set("gender", "male");
	set("long",
		"一個眼明手快的小夥計﹐肩上搭著一條雪白的抹布﹐在桌椅之\n"
		"間穿梭招呼。你可以用 list 看可以點什麼﹐用 buy 跟店小二點\n"
		"菜。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"店小二脆生生地吆喝道﹕客官您點什麼﹖小店的招牌菜可多著哩﹗\n",
		"店小二一面擦桌子﹐一面哼著時興的小調兒。\n",
	}));
	set("merchandise", ([
		"/obj/food/manto" : 50,
		"/obj/food/dumpling" : 50,
		"/obj/food/pork" : 40,
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
