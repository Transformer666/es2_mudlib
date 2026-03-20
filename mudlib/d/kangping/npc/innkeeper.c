// innkeeper.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("客店老闆", ({"innkeeper", "boss"}));
	set_race("human");
	set_class("commoner");
	set_level(8);

	set("age", 50);
	set("gender", "male");
	set("long",
		"一個憨厚老實的中年漢子﹐臉上總掛著樸實的笑容。他經營這\n"
		"家小客店已經二十多年了﹐雖然生意冷清﹐但待客十分殷勤。你可\n"
		"以用 list 看看有什麼﹐用 buy 來買。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"老闆笑道﹕客倌﹐嚐嚐小店自製的草藥茶﹐提神醒腦哩。\n",
		"老闆擦著桌子﹐嘮叨道﹕這村子太偏僻了﹐難得來個客人。\n",
	}));
	set("merchandise", ([
		__DIR__"obj/herb_tea" : 50,
		__DIR__"obj/straw_sandal" : 20,
	]));

	setup();
	carry_money("coin", 80);
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
}

int accept_fight(object ob)
{
	do_chat("老闆連忙擺手道﹕客倌﹐有話好說﹐千萬別動手﹗\n");
	return 0;
}

void deliver_merchandise(object customer, mixed item)
{
	command("say " + item->name() + "﹐請拿好。");
	::deliver_merchandise(customer, item);
}
