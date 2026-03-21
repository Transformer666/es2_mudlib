// fog_snake.c

#include <npc.h>

inherit F_FIGHTER;

void create()
{
	set_name("霧蛇", ({"fog_snake", "snake"}));
	set_attr("str", 18);
	set_attr("con", 16);
	set_attr("dex", 24);
	set_race("animal");
	set_class("fighter");
	set_level(12);

	set_skill("unarmed", 50);
	set_skill("dodge", 50);

	set("age", 10);
	set("gender", "female");
	set("long",
		"一條三尺多長的灰白色毒蛇﹐通體佈滿了如霧氣般朦朧的花紋。\n"
		"它悄無聲息地在濃霧中游走﹐吐著猩紅的信子﹐一雙豎瞳冷冷\n"
		"地盯著獵物。\n");
	set("attitude", "aggressive");
	setup();
	carry_money("coin", 30);
}
