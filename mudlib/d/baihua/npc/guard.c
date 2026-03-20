// NPC: /d/baihua/npc/guard.c

#include <npc.h>

inherit F_SOLDIER;

void create()
{
	set_name("護村壯丁", ({"guard", "villager"}));
	set_race("human");
	set_class("fighter");
	set_level(12);

	set("age", 30);
	set("gender", "male");
	set_skill("staff", 50);
	set_skill("parry", 40);
	set_skill("dodge", 35);

	set("long",
		"一個膀大腰圓的壯漢﹐手持一根哨棒﹐負責看守村口。他雖然\n"
		"不是正規軍人﹐但一身蠻力﹐足以嚇退普通的毛賊。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"壯丁打了個哈欠﹐說道﹕這村子太平得很﹐沒什麼事。\n",
		"壯丁左右張望了一下﹐又靠回牆上。\n",
	}));

	setup();
	carry_object(STOCK_WEAPON("staff"))->wield();
	carry_money("coin", 30);
}
