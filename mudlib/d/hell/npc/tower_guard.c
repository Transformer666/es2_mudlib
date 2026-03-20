#include <npc.h>

inherit F_FIGHTER;

void create()
{
	set_name("陰魂守衛", ({"tower_guard", "guard", "yinhun"}));
	set_attr("str", 20);
	set_attr("con", 22);
	set_attr("dex", 18);
	set_attr("spi", 24);
	set_race("human");
	set_class("commoner");
	set_level(35);

	set_skill("blade", 70);
	set_skill("dodge", 60);
	set_skill("parry", 55);

	set("age", 0);
	set("long",
		"一團凝聚成人形的陰暗氣息﹐隱約可見身披殘破鎧甲的身影。\n"
		"它手持一柄漆黑的彎刀﹐雙目中燃燒著幽綠的鬼火﹐守衛著地\n"
		"氣塔不讓任何人靠近。\n");

	set("chat_chance", 2);
	set("chat_msg", ({
		"陰魂守衛發出一聲淒厲的嚎叫﹐令人毛骨悚然。\n",
		"陰魂守衛手中的彎刀閃過一道幽光。\n",
	}));

	setup();
	carry_object( STOCK_ARMOR("cloth") )->wear();
	carry_object( STOCK_WEAPON("blade") )->wield();
	set_temp("apply/vision_of_ghost", 1);
}
