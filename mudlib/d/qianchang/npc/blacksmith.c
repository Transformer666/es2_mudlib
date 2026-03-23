// NPC: /d/qianchang/npc/blacksmith.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("鐵匠", ({"blacksmith", "smith"}));
	set_race("human");
	set_class("commoner");
	set_level(12);
	set_attr("str", 20);
	set_attr("con", 18);

	set("age", 45);
	set("gender", "male");
	set("long",
		"一個身材魁梧的中年漢子，裸著上身露出一身結實的肌肉，手\n"
		"臂上佈滿了燙傷留下的疤痕。他額頭上滲著汗珠，正揮舞著大錘\n"
		"在鐵砧上敲打著一塊燒得通紅的鐵塊。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"鐵匠擦了把汗道：打鐵這活兒，講究的是火候和力道。\n",
		"鐵匠叮叮噹噹地敲打著，火星四濺。\n",
		"鐵匠抬頭看了你一眼：要打什麼傢伙，儘管開口。\n",
	}));

	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
}
