// vim: syntax=lpc

#include <npc.h>

inherit F_FIGHTER;

void create()
{
	set_name("神衛", ({"shenwei", "shen wei"}));
	set_attr("str", 28);
	set_attr("dex", 22);
	set_attr("con", 28);
	set_attr("int", 18);
	set_attr("spi", 20);
	set_attr("wis", 16);
	set_race("human");
	set_class("commoner");
	set_level(55);
	advance_stat("gin", 200);
	advance_stat("kee", 200);
	advance_stat("sen", 200);

	set_skill("pike", 100);
	set_skill("dodge", 70);
	set_skill("parry", 85);
	set_skill("force", 70);

	set("age", 40);
	set("gender", "male");
	set("long",
		"神衛是風神座下四大護衛之一﹐身穿灰白色戰甲﹐體型魁梧﹐\n"
		"手持一桿長槍﹐如同一座不可撼動的山嶽。他是四大護衛中防禦\n"
		"最強的一位﹐負責守衛遺跡的入口。\n");
	setup();
	carry_object(STOCK_WEAPON("pike"))->wield();
	carry_object(STOCK_ARMOR("cloth"))->wear();

	add_temp("apply/attack", 45);
	add_temp("apply/defense", 60);
	add_temp("apply/damage", 25);
	add_temp("apply/armor", 55);
}
