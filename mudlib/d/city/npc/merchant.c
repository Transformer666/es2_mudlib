// NPC: /d/city/npc/merchant.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("雜貨商", ({"merchant", "trader"}));
	set_race("human");
	set_class("commoner");
	set_level(8);

	set("age", 42);
	set("long",
		"一個精明的商人，穿著體面的綢袍，腰間繫著鼓鼓的錢袋。\n"
		"他熱情地招呼每一位經過的客人，推銷著自己的貨品。\n"
		"你可以用 list 看看他的貨品。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"商人吆喝道：上等貨色，物美價廉！\n",
		"商人笑著說：客倌來瞧瞧，保證不讓您失望！\n",
	}));
	set("merchandise", ([
		STOCK_MEDICATION("black_pill") : 50,
		STOCK_MEDICATION("boar_berry") : 40,
		STOCK_MEDICATION("wild_ginseng") : 30,
	]));

	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
	carry_money("coin", 500);
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
}

int accept_fight(object ob)
{
	do_chat("商人連忙擺手道：客倌息怒，有話好說！\n");
	return 0;
}
