// stone_lion.c

#include <npc.h>

inherit F_FIGHTER;

void create()
{
	set_name("石獅子", ({"stone_lion", "lion"}));
	set_attr("str", 14);
	set_attr("con", 20);
	set_attr("dex", 8);
	set_race("golem");
	set_class("fighter");
	set_level(8);

	set_skill("unarmed", 40);
	set_skill("parry", 50);

	set("age", 100);
	set("gender", "male");
	set("long",
		"村口牌坊旁蹲著一隻石獅子﹐通體由青石雕成﹐造型威武。歲\n"
		"月的侵蝕讓它的面容有些模糊﹐但那雙圓瞪的石眼仍然散發著一\n"
		"股威嚴之氣。\n");
	setup();
	carry_money("coin", 20);
}
