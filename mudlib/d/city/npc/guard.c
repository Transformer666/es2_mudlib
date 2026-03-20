// NPC: /d/city/npc/guard.c

#include <npc.h>

inherit F_SOLDIER;

void create()
{
	set_name("城衛", ({"guard", "city guard"}));
	set_race("human");
	set_class("soldier");
	set_level(25);

	set("age", 30);
	set("long",
		"一名身披鐵甲的城衛，面容剛毅，目光犀利。他手持一柄長槍，\n"
		"腰間還挎著一把佩刀，渾身上下散發著一股凜然正氣。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"城衛目光如炬地掃視四周。\n",
		"城衛沉聲道：閒雜人等，不得滋事！\n",
	}));

	setup();
	carry_money("coin", 100);
	carry_object(STOCK_WEAPON("pike"))->wield();
	carry_object(STOCK_ARMOR("iron_armor"))->wear();
}
