// vim: syntax=lpc

#include <npc.h>

inherit F_FIGHTER;

void create()
{
	set_name("練功木人", ({"training_dummy", "dummy", "wooden_man"}));
	set_attr("str", 15);
	set_attr("dex", 10);
	set_attr("con", 30);
	set_attr("int", 1);
	set_attr("spi", 1);
	set_race("human");
	set_class("fighter");
	set_level(20);

	set_skill("unarmed", 1);
	set_skill("dodge", 1);
	set_skill("parry", 20);

	set("age", 1);
	set("gender", "male");
	set("long",
		"一個以堅硬木材製成的練功木人，身上佈滿了刀痕劍跡。雖然只是\n"
		"個木頭人，但精巧的機關使它能做出簡單的防禦動作。\n");
	setup();
}
