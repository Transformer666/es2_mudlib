// black_bear.c

#include <npc.h>

inherit F_FIGHTER;

void create()
{
	set_name("黑熊", ({"black_bear", "bear"}));
	set_attr("str", 30);
	set_attr("con", 28);
	set_attr("dex", 14);
	set_race("animal");
	set_class("fighter");
	set_level(25);

	set_skill("unarmed", 85);
	set_skill("dodge", 40);
	set_skill("parry", 30);

	set("age", 12);
	set("long",
		"一頭巨大的黑熊﹐站起來足有一人多高。渾身漆黑的毛皮油光\n"
		"發亮﹐胸前有一塊白色的V形斑紋。它四肢粗壯﹐爪子又長又尖﹐\n"
		"正用一雙小眼睛警惕地盯著你。\n");
	set("aggressive", 1);
	setup();
	carry_money("coin", 100);
}
