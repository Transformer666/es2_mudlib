// NPC: /d/city/npc/innkeeper.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("掌櫃", ({"innkeeper", "shopkeeper"}));
	set_race("human");
	set_class("commoner");
	set_level(12);

	set("age", 50);
	set("long",
		"天風客棧的掌櫃是個白白胖胖的中年人，臉上總掛著和氣的笑容。\n"
		"他穿著一身錦緞長袍，手裡搖著一把摺扇，一副生意興隆的模樣。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"掌櫃笑呵呵地說：客倌請坐，好酒好菜馬上就來！\n",
		"掌櫃招呼夥計道：快給客倌上壺好茶！\n",
		"掌櫃一邊算帳一邊哼著小調。\n",
	}));

	setup();
	carry_money("coin", 300);
	carry_object(STOCK_ARMOR("cloth"))->wear();
}
