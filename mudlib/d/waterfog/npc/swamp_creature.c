// swamp_creature.c

#include <npc.h>

inherit F_FIGHTER;

void create()
{
	set_name("沼澤怪", ({"swamp_creature", "creature"}));
	set_attr("str", 26);
	set_attr("con", 24);
	set_attr("dex", 14);
	set_race("monster");
	set_class("fighter");
	set_level(16);

	set_skill("unarmed", 60);
	set_skill("dodge", 35);
	set_skill("parry", 40);

	set("age", 50);
	set("gender", "male");
	set("long",
		"一團由腐爛的水草和污泥凝聚而成的怪物﹐散發著令人窒息的\n"
		"惡臭。它的身體不斷滴落著黑色的泥漿﹐兩隻渾濁的眼睛從泥\n"
		"團中透出詭異的綠光。\n");
	set("attitude", "aggressive");
	setup();
	carry_money("coin", 55);
}
