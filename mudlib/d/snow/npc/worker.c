// NPC: /d/snow/npc/worker.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("倉庫工人", ({"worker"}));
	set_attr("str", 16);
	set_attr("dex", 12);
	set_attr("con", 18);
	set_attr("int", 10);
	set_attr("wis", 10);
	set_attr("spi", 10);
	set_race("human");
	set_class("commoner");
	set_level(5);

	set("age", 35);
	set("gender", "male");
	set("long",
		"一個壯碩的漢子﹐穿著粗布短褂﹐正賣力地搬著木箱。他的\n"
		"額頭上滿是汗珠﹐但臉上帶著樸實的笑容。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"倉庫工人擦了擦額頭上的汗水﹐繼續搬著貨物。\n",
		"倉庫工人嘟囔道：今天的貨真多啊。\n",
	}));

	setup();
	carry_money("coin", 15);
	carry_object(STOCK_ARMOR("cloth"))->wear();
}
