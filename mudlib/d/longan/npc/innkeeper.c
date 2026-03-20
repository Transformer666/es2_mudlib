// NPC: /d/longan/npc/innkeeper.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("掌櫃", ({"innkeeper", "shopkeeper"}));
	set_race("human");
	set_class("commoner");
	set_level(10);

	set("age", 45);
	set("long",
		"一個精明幹練的中年男子，穿著一身靛藍色的綢袍，腰間繫著\n"
		"一串銅鑰匙。他目光如炬，一邊撥弄著算盤，一邊招呼著來往的\n"
		"客人，舉止間透露出商人特有的精明和練達。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"掌櫃笑道：客倌，小店的招牌菜可是龍安燒雞，來一隻？\n",
		"掌櫃一邊擦拭杯盞，一邊哼著小曲。\n",
	}));

	setup();
	carry_money("coin", 200);
	carry_object(STOCK_ARMOR("cloth"))->wear();
}
