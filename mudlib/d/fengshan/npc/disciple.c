#include <npc.h>

inherit F_FIGHTER;

void create()
{
	set_name("封山弟子", ({"disciple", "fengshan_disciple"}));
	set_attr("str", 14);
	set_attr("con", 13);
	set_attr("dex", 16);
	set_race("human");
	set_class("warrior");
	set_level(20);

	set_skill("sword", 40);
	set_skill("dodge", 35);
	set_skill("parry", 30);

	set("age", 22);
	set("long",
		"一名身穿素色勁裝的封山派弟子﹐腰間懸著一柄長劍﹐神態沉穩。\n");
	setup();
	carry_object( STOCK_ARMOR("cloth") )->wear();
	carry_object( STOCK_WEAPON("longsword") )->wield();
	carry_money("coin", 50);
}
