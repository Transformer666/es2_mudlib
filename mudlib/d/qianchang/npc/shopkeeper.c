// NPC: /d/qianchang/npc/shopkeeper.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("雜貨店老闆", ({"shopkeeper", "shop owner"}));
	set_race("human");
	set_class("commoner");
	set_level(10);

	set("age", 40);
	set("gender", "male");
	set("long",
		"一個精明的中年商人，眼睛不大卻總是滴溜溜地轉，打量著每\n"
		"一位走進店裡的客人。他穿著一件洗得發白的藍布長衫，腰間別\n"
		"著一串鑰匙。你可以用 list 看看有什麼﹐用 buy 來買。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"雜貨店老闆招呼道：客官看看，都是實用的好貨。\n",
		"雜貨店老闆撥弄著算盤珠子，嘴裡念念有詞。\n",
		"雜貨店老闆整理著貨架上的東西，嘴裡嘟囔著：又該進貨了。\n",
	}));
	set("merchandise", ([
		STOCK_ITEM("ration") : 40,
		STOCK_ITEM("torch") : 20,
	]));

	setup();
	carry_money("coin", 200);
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
}

int accept_fight(object ob)
{
	do_chat("雜貨店老闆連忙擺手道：大俠饒命﹐小的只是個賣貨的﹗\n");
	return 0;
}

void deliver_merchandise(object customer, mixed item)
{
	command("say " + item->name() + "﹐拿好嘍。");
	::deliver_merchandise(customer, item);
}
