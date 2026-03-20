#include <npc.h>

inherit F_SOLDIER;

void create()
{
	set_name("操練士兵", ({"soldier", "zhenwu_soldier"}));
	set_attr("str", 14);
	set_attr("con", 14);
	set_attr("dex", 12);
	set_race("human");
	set_class("soldier");
	set_level(15);

	set_skill("blade", 30);
	set_skill("dodge", 25);

	set("age", 24);
	set("long",
		"一名正在校場上操練的士兵﹐身穿軍服﹐汗流浹背﹐卻仍然\n"
		"一絲不苟地反覆演練著刀法。\n");
	setup();
	carry_object( STOCK_ARMOR("cloth") )->wear();
	carry_object( STOCK_WEAPON("blade") )->wield();
	carry_money("coin", 40);
}
