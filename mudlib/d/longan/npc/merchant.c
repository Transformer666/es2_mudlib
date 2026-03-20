// NPC: /d/longan/npc/merchant.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("雜貨商人", ({"merchant", "trader"}));
	set_race("human");
	set_class("commoner");
	set_level(5);

	set("age", 38);
	set("gender", "male");
	set("long",
		"一個精明幹練的商人，身穿靛藍色的錦袍，腰間繫著一個鼓鼓囊\n"
		"囊的錢袋。他笑容滿面地招呼著來往的客人，不時吆喝著推銷自己\n"
		"的貨品。你可以用 list 看看他的貨品。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"商人吆喝道：走過路過不要錯過，上等貨色，童叟無欺！\n",
		"商人熱情地說道：客倌要不要看看？保證物美價廉！\n",
		"商人擦了擦額頭上的汗珠，又忙碌地整理起貨物來。\n",
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
