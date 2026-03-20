// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("茶博士", ({"tea_vendor", "tea_master", "chaboshi"}));
	set_race("human");
	set_class("commoner");
	set_level(8);

	set("age", 50);
	set("gender", "male");
	set("long",
		"一位儒雅的中年男子，身穿素淨的棉布長袍，正以嫻熟的手法\n"
		"沖泡著香茗。他的茶館供應各種名茶，香氣四溢。你可以用 list\n"
		"看看他的茶單。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"茶博士微笑道：品茶講究的是心境，心靜方能品出真味。\n",
		"茶博士一邊沏茶一邊說：這碧螺春可是今年的新茶，清香甘甜。\n",
		"茶博士悠然道：茶道之妙，在乎一心。客倌請慢用。\n",
	}));
	set("merchandise", ([
		STOCK_MEDICATION("flower_pill") : 30,
		STOCK_MEDICATION("wild_ginseng") : 20,
	]));

	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
	carry_money("coin", 200);
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
}

int accept_fight(object ob)
{
	do_chat("茶博士連忙說道：客倌請息怒，茶館乃清淨之地，不宜動武。\n");
	return 0;
}
