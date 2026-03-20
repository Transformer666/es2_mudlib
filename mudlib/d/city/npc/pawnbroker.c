// NPC: /d/city/npc/pawnbroker.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("當鋪掌櫃", ({"pawnbroker", "broker"}));
	set_race("human");
	set_class("commoner");
	set_level(10);

	set("age", 58);
	set("long",
		"一個精瘦的老頭，戴著一副厚厚的老花鏡，目光在鏡片後面\n"
		"閃爍著精明的光芒。他的手指細長靈活，正在仔細鑑定一件古\n"
		"玩的真偽。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"掌櫃透過老花鏡審視著一件玉佩，嘖嘖稱奇。\n",
		"掌櫃嘀咕道：這年頭，假貨越來越多了……\n",
	}));

	setup();
	carry_money("coin", 1000);
	carry_object(STOCK_ARMOR("cloth"))->wear();
}
