// NPC: /d/weiguo/npc/innkeeper.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("老兵掌櫃", ({"innkeeper", "veteran"}));
	set_race("human");
	set_class("commoner");
	set_level(15);

	set("age", 55);
	set("gender", "male");
	set("long",
		"一個身材魁梧的老兵，左臉上有一道長長的刀疤，那是他當年\n"
		"在邊境作戰時留下的。退伍之後他在這裡開了間客棧，專門招待過\n"
		"往的戍邊將士和行商旅人。他說話嗓門極大，性格豪爽。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"老兵掌櫃拍著桌子大聲道：來來來，喝碗烈酒暖暖身子！\n",
		"老兵掌櫃摸著臉上的刀疤，似乎在回憶往事。\n",
	}));
	set("merchandise", ([
		STOCK_ITEM("ration") : 50,
		STOCK_ITEM("torch") : 50,
	]));

	setup();
	carry_money("coin", 150);
	carry_object(STOCK_ARMOR("cloth"))->wear();
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
}
