// vim: syntax=lpc

#include <npc.h>

inherit F_FIGHTER;

void create()
{
	set_name("滅心", ({"miexin", "mie xin"}));
	set_attr("str", 26);
	set_attr("dex", 24);
	set_attr("con", 24);
	set_attr("int", 20);
	set_attr("spi", 22);
	set_attr("wis", 18);
	set_race("human");
	set_class("commoner");
	set_level(55);
	advance_stat("gin", 200);
	advance_stat("kee", 200);
	advance_stat("sen", 200);

	set_skill("sword", 100);
	set_skill("dodge", 80);
	set_skill("parry", 75);
	set_skill("force", 70);

	set("age", 35);
	set("gender", "male");
	set("long",
		"滅心是風神座下四大護衛之一﹐身穿灰白色戰袍﹐面無表情﹐\n"
		"一雙死灰般的眼睛透著冷酷無情的殺意。他手持長劍﹐忠誠地\n"
		"守衛著這片古老的遺跡。\n");
	setup();
	carry_object(STOCK_WEAPON("longsword"))->wield();
	carry_object(STOCK_ARMOR("cloth"))->wear();

	add_temp("apply/attack", 50);
	add_temp("apply/defense", 50);
	add_temp("apply/damage", 30);
	add_temp("apply/armor", 40);
	set_temp("apply/vision_of_ghost", 1);
}
