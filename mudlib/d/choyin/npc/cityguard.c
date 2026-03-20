// cityguard.c

#include <npc.h>

inherit F_SOLDIER;

void create()
{
	set_name("縣城守衛", ({"cityguard", "guard"}));
	set_attr("str", 18);
	set_attr("con", 16);
	set_attr("dex", 14);
	set_race("human");
	set_class("fighter");
	set_level(18);

	set_skill("sword", 60);
	set_skill("dodge", 50);
	set_skill("parry", 40);

	set("age", 25);
	set("gender", "male");
	set("long",
		"一名喬陰縣城的守衛﹐身穿皂色短衣﹐腰佩腰刀﹐頭戴皂帽﹐\n"
		"看起來頗為精神。他雙目炯炯有神﹐不時掃視著來往的行人。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"守衛打了個哈欠﹐四下張望了一番。\n",
		"守衛說道﹕最近松林裡不太平﹐各位出城要小心。\n",
	}));
	setup();
	carry_object( STOCK_WEAPON("longsword") )->wield();
	carry_money("coin", 60);
}
