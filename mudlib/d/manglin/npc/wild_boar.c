// wild_boar.c

#include <npc.h>

inherit F_FIGHTER;

void create()
{
	set_name("野豬", ({"wild_boar", "boar"}));
	set_attr("str", 22);
	set_attr("con", 20);
	set_attr("dex", 12);
	set_race("animal");
	set_class("fighter");
	set_level(18);

	set_skill("unarmed", 65);
	set_skill("dodge", 35);

	set("age", 8);
	set("long",
		"一頭體型碩大的野豬﹐渾身灰褐色的鬃毛又粗又硬﹐嘴裡露出\n"
		"兩根鋒利的獠牙。它正在地上拱來拱去地覓食﹐不時發出哼哼的聲\n"
		"音﹐看起來十分暴躁。\n");
	set("aggressive", 1);
	setup();
	carry_money("coin", 50);
}
