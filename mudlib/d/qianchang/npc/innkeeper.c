// NPC: /d/qianchang/npc/innkeeper.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("客棧掌櫃", ({"innkeeper", "keeper"}));
	set_race("human");
	set_class("commoner");
	set_level(8);

	set("age", 50);
	set("gender", "male");
	set("long",
		"一個胖墩墩的中年男子，圓臉上總是掛著和氣的笑容。他穿著\n"
		"一件油漬斑斑的圍裙，手裡拎著一塊抹布，不停地擦拭著桌椅。\n"
		"看得出來是個勤快本分的生意人。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"客棧掌櫃笑道：客倌，小店的滷肉飯可是一絕，來一碗？\n",
		"客棧掌櫃一邊收拾碗碟，一邊嘆道：今天客人不多啊。\n",
		"客棧掌櫃擦了擦額頭的汗：住店的樓上請，吃飯的這邊坐。\n",
	}));

	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
}
