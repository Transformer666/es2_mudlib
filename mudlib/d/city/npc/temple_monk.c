// NPC: /d/city/npc/temple_monk.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("廟祝", ({"temple monk", "monk"}));
	set_race("human");
	set_class("monk");
	set_level(15);

	set("age", 60);
	set("long",
		"一位身穿灰色道袍的老廟祝，須髮皆白，面容慈祥。他手持\n"
		"一串佛珠，正在低聲誦經，周身散發著一股祥和的氣息。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"廟祝低聲誦念著經文，神情肅穆。\n",
		"廟祝合掌道：施主有禮了。\n",
	}));

	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
}
