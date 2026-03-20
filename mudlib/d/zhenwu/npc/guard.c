#include <npc.h>

inherit F_SOLDIER;

void create()
{
	set_name("營門衛兵", ({"guard", "zhenwu_guard"}));
	set_attr("str", 16);
	set_attr("con", 15);
	set_attr("dex", 13);
	set_race("human");
	set_class("soldier");
	set_level(20);

	set_skill("pike", 40);
	set_skill("dodge", 30);
	set_skill("parry", 35);

	set("age", 28);
	set("long",
		"一名全副武裝的振武軍營衛兵﹐身穿鐵甲﹐手持長戟﹐神態\n"
		"嚴肅﹐目光警覺地注視著每一個進出營門的人。\n");
	setup();
	carry_object( STOCK_ARMOR("cloth") )->wear();
	carry_object( STOCK_WEAPON("pike") )->wield();
	carry_money("coin", 60);
}
