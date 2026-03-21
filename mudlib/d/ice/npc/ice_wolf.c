// ice_wolf.c

#include <npc.h>

inherit F_FIGHTER;

void create()
{
	set_name("冰狼", ({"ice_wolf", "wolf"}));
	set_attr("str", 24);
	set_attr("con", 22);
	set_attr("dex", 20);
	set_race("animal");
	set_class("fighter");
	set_level(15);

	set_skill("unarmed", 60);
	set_skill("dodge", 50);
	set_skill("parry", 30);

	set("age", 7);
	set("gender", "male");
	set("long",
		"一隻通體雪白的冰狼﹐皮毛如雪般潔白﹐在冰天雪地中幾乎\n"
		"難以辨認。它的雙眼呈幽藍色﹐彷彿凝聚了冰原的寒意﹐呼出\n"
		"的氣息在空氣中凝結成白霧。\n");
	set("attitude", "aggressive");
	setup();
	carry_money("coin", 50);
}
