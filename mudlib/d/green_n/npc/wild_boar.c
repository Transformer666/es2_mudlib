// NPC: /d/green_n/npc/wild_boar.c

#include <npc.h>

inherit F_FIGHTER;

void create()
{
	set_name("野豬", ({"wild boar", "boar"}));
	set_race("animal");
	set_class("commoner");
	set_level(18);

	set("age", 8);
	set("long",
		"一頭體型龐大的野豬，渾身覆蓋著粗硬的鬃毛。牠的獠牙又\n"
		"長又尖，從嘴角向上彎曲，看起來威力十足。牠正在岩石間翻\n"
		"找著食物，不時發出粗重的哼哼聲。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"野豬用鼻子拱著地上的泥土，尋找食物。\n",
		"野豬警覺地抬起頭，鼻子使勁嗅了嗅。\n",
	}));
	set("attitude", "aggressive");

	setup();
}
