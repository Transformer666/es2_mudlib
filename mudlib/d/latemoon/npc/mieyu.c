// vim: syntax=lpc

#include <npc.h>

inherit F_FIGHTER;

void create()
{
	set_name("滅慾", ({"mieyu", "mie yu"}));
	set_attr("str", 22);
	set_attr("dex", 28);
	set_attr("con", 22);
	set_attr("int", 24);
	set_attr("spi", 26);
	set_attr("wis", 22);
	set_race("human");
	set_class("commoner");
	set_level(55);
	advance_stat("gin", 200);
	advance_stat("kee", 200);
	advance_stat("sen", 200);

	set_skill("needle", 100);
	set_skill("dodge", 90);
	set_skill("parry", 65);
	set_skill("force", 75);

	set("age", 28);
	set("gender", "female");
	set("long",
		"滅慾是風神座下四大護衛之一﹐身穿灰白色戰袍﹐容貌清冷如\n"
		"冰霜﹐手持數枚銀針﹐針法精準致命。她是四大護衛中最年輕的\n"
		"一位﹐卻也是最令人畏懼的。\n");
	set("attitude", "aggressive");
	setup();
	carry_object(STOCK_WEAPON("needle"))->wield();
	carry_object(STOCK_ARMOR("cloth"))->wear();

	add_temp("apply/attack", 55);
	add_temp("apply/defense", 45);
	add_temp("apply/damage", 35);
	add_temp("apply/armor", 35);
	set_temp("apply/vision_of_ghost", 1);
}
