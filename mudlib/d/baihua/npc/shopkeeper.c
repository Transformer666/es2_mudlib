// NPC: /d/baihua/npc/shopkeeper.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("雜貨商", ({"shopkeeper", "merchant"}));
	set_race("human");
	set_class("commoner");
	set_level(7);

	set("age", 35);
	set("gender", "female");
	set("long",
		"一個面容和善的中年婦人﹐穿著素淨的碎花衣裳﹐頭上簪著一朵\n"
		"小白花。她是這間雜貨舖的老闆娘﹐做事利索﹐待人熱情。你可以\n"
		"用 list 看看有什麼﹐用 buy 來買。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"老闆娘笑道﹕百花村的東西都是好東西﹐客官看看﹗\n",
		"老闆娘整理著貨架﹐嘴裡哼著小曲兒。\n",
	}));
	set("merchandise", ([
		__DIR__"obj/flower_bundle" : 15,
		__DIR__"obj/wreath" : 30,
	]));

	setup();
	carry_money("coin", 50);
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
}

int accept_fight(object ob)
{
	do_chat("老闆娘尖聲叫道﹕你要幹什麼﹗來人啊﹗\n");
	return 0;
}

void deliver_merchandise(object customer, mixed item)
{
	command("say " + item->name() + "﹐拿好嘍。");
	::deliver_merchandise(customer, item);
}
