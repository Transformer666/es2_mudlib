// vim: syntax=lpc

#include <npc.h>

inherit F_FIGHTER;

void create()
{
	set_name("滅名", ({"mieming", "mie ming"}));
	set_attr("str", 24);
	set_attr("dex", 26);
	set_attr("con", 22);
	set_attr("int", 22);
	set_attr("spi", 24);
	set_attr("wis", 20);
	set_race("human");
	set_class("commoner");
	set_level(55);
	advance_stat("gin", 200);
	advance_stat("kee", 200);
	advance_stat("sen", 200);

	set_skill("blade", 100);
	set_skill("dodge", 85);
	set_skill("parry", 70);
	set_skill("force", 70);

	set("age", 32);
	set("gender", "male");
	set("long",
		"滅名是風神座下四大護衛之一﹐身穿灰白色戰袍﹐沉默寡言﹐\n"
		"手持一把寒光閃爍的長刀。他的刀法迅捷凌厲﹐出手毫不留情。\n");
	setup();
	carry_object(STOCK_WEAPON("blade"))->wield();
	carry_object(STOCK_ARMOR("cloth"))->wear();

	add_temp("apply/attack", 50);
	add_temp("apply/defense", 50);
	add_temp("apply/damage", 30);
	add_temp("apply/armor", 40);
	set_temp("apply/vision_of_ghost", 1);
}
