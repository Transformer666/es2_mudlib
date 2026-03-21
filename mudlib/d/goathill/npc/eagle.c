// eagle.c

#include <npc.h>

inherit F_FIGHTER;

void create()
{
	set_name("蒼鷹", ({"eagle"}));
	set_attr("str", 16);
	set_attr("con", 14);
	set_attr("dex", 26);
	set_race("animal");
	set_class("fighter");
	set_level(10);

	set_skill("unarmed", 45);
	set_skill("dodge", 55);

	set("age", 8);
	set("gender", "male");
	set("long",
		"一隻翼展超過兩米的蒼鷹﹐渾身覆蓋著灰褐色的羽毛﹐腹部\n"
		"呈白色。它那鉤狀的喙和鋒利的爪子閃著寒光﹐銳利的雙眼正\n"
		"虎視眈眈地俯瞰著四周。\n");
	set("attitude", "aggressive");
	setup();
	carry_money("coin", 25);
}
