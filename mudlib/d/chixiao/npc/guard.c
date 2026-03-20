// NPC: /d/chixiao/npc/guard.c

#include <npc.h>

inherit F_SOLDIER;

void create()
{
	set_name("赤魈守衛", ({"guard"}));
	set_attr("str", 16);
	set_attr("dex", 14);
	set_attr("con", 15);
	set_attr("int", 10);
	set_attr("spi", 10);
	set_attr("wis", 10);
	set_race("human");
	set_class("soldier");
	set_level(12);
	set_skill("blade", 35);
	set_skill("parry", 25);
	set_skill("dodge", 20);
	set("age", 30);
	set("gender", "male");
	set("long",
		"一名面色黝黑的村莊守衛﹐手持砍刀﹐警覺地守在村口。他的\n"
		"眼神中透著疲憊和不安﹐似乎這個村子經常遭到什麼東西的侵擾。\n");

	setup();
	carry_object(STOCK_WEAPON("blade"))->wield();
	carry_object(STOCK_ARMOR("armor"))->wear();
}
