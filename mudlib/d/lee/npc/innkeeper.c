// innkeeper.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("客棧老闆", ({"innkeeper", "boss"}));
	set_race("human");
	set_class("commoner");
	set_level(6);

	set("age", 45);
	set("gender", "male");
	set("long",
		"一個老實巴交的漢子﹐圓臉﹐笑起來眼睛瞇成一條線。他是\n"
		"李家村本地人﹐開著這間小客棧已有十來年了。你可以用 list 看\n"
		"看有什麼﹐用 buy 來買。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"老闆笑道﹕客倌﹐嚐嚐我們李家的豆腐﹐保管你吃了還想吃。\n",
		"老闆說道﹕我們村子雖小﹐但民風淳樸﹐住著舒服。\n",
	}));
	set("merchandise", ([
		__DIR__"obj/tofu" : 50,
		__DIR__"obj/hoe" : 10,
	]));

	setup();
	carry_money("coin", 60);
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
}

int accept_fight(object ob)
{
	do_chat("老闆連忙擺手道﹕客倌﹐有話好說﹐別動手。\n");
	return 0;
}

void deliver_merchandise(object customer, mixed item)
{
	command("say " + item->name() + "﹐請拿好。");
	::deliver_merchandise(customer, item);
}
