#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("灰袍僧人", ({"monk", "baixiang_monk"}));
	set_attr("str", 12);
	set_attr("con", 14);
	set_attr("dex", 11);
	set_attr("wis", 16);
	set_attr("spi", 15);
	set_race("human");
	set_class("monk");
	set_level(12);

	set_skill("staff", 20);
	set_skill("dodge", 15);

	set("age", 35);
	set("attitude", "peaceful");
	set("long",
		"一位身穿灰色僧袍的僧人﹐手持念珠﹐沿著菩提樹下的青石\n"
		"小路緩緩行走﹐口中低聲誦念佛經﹐神態安詳。\n");
	setup();
	carry_object( STOCK_ARMOR("cloth") )->wear();
	carry_money("coin", 10);
	set_temp("apply/vision_of_ghost", 1);
}
