// NPC: /d/green_n/npc/wild_wolf.c

#include <npc.h>

inherit F_FIGHTER;

void create()
{
	set_name("草原野狼", ({"wild wolf", "wolf"}));
	set_race("animal");
	set_class("commoner");
	set_level(15);

	set("age", 5);
	set("long",
		"一匹灰色的草原野狼，體型健碩，毛色油亮。牠的眼睛泛著\n"
		"幽綠的光芒，尖利的獠牙露在嘴角外面，看起來十分兇悍。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"野狼低沉地咆哮著，警惕地注視著四周。\n",
		"野狼搖著尾巴在草叢中來回踱步。\n",
	}));

	setup();
}
