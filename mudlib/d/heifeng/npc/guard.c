// guard.c

#include <npc.h>

inherit F_FIGHTER;

void create()
{
	set_name("山寨守門人", ({"guard", "gatekeeper"}));
	set_attr("str", 24);
	set_attr("con", 22);
	set_attr("dex", 18);
	set_race("human");
	set_class("fighter");
	set_level(25);

	set_skill("axe", 80);
	set_skill("dodge", 60);
	set_skill("parry", 55);

	set("age", 35);
	set("long",
		"黑風寨的守門人﹐身材壯碩﹐一臉凶相。他手持一把大鐵斧﹐\n"
		"往寨門前一站﹐頗有一夫當關萬夫莫開之勢。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"守門人喝道﹕站住﹗哪裡來的﹖口令﹗\n",
		"守門人狠狠地盯著你﹐手中的斧頭握得更緊了。\n",
	}));
	set("aggressive", 1);
	setup();
	carry_object(__DIR__"obj/iron_axe")->wield();
	carry_object( STOCK_ARMOR("cloth") )->wear();
	carry_money("coin", 150);
}
