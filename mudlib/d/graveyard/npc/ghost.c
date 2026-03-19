// ghost.c

#include <npc.h>

inherit F_FIGHTER;

void create()
{
	set_name("孤魂野鬼", ({"ghost", "spirit"}));
	set_attr("str", 14);
	set_attr("con", 12);
	set_attr("dex", 24);
	set_race("undead");
	set_class("fighter");
	set_level(15);

	set_skill("unarmed", 60);
	set_skill("dodge", 80);

	set("age", 100);
	set("long",
		"一團模糊的綠色光影在空中飄忽不定﹐隱約可以看出是一個人形\n"
		"的輪廓。它發出淒厲的嗚咽聲﹐像是在訴說著什麼冤屈。當它飄過\n"
		"你身邊時﹐你能感覺到一陣徹骨的寒意。\n");
	set("aggressive", 1);
	setup();
	carry_money("coin", 50);
}
