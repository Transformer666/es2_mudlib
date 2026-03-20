// NPC: /d/chixiao/npc/innkeeper.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("客棧老闆娘", ({"innkeeper", "boss"}));
	set_race("human");
	set_class("commoner");
	set_level(8);

	set("age", 45);
	set("gender", "female");
	set("long",
		"一個面容憔悴的中年婦人﹐眼角佈滿了皺紋﹐卻透著一股堅韌\n"
		"的神情。她獨自經營著這間小客棧﹐手腳十分利落。你可以用\n"
		"list 看看有什麼﹐用 buy 來買。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"老闆娘嘆道﹕這村子不太平﹐住客少得可憐。\n",
		"老闆娘一邊擦桌子一邊說﹕客倌﹐喝碗酒暖暖身子吧。\n",
	}));
	set("merchandise", ([
		__DIR__"obj/spirit_wine" : 50,
	]));

	setup();
	carry_money("coin", 60);
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
}

int accept_fight(object ob)
{
	do_chat("老闆娘怒道﹕你想幹什麼﹗這裡不準動手﹗\n");
	return 0;
}

void deliver_merchandise(object customer, mixed item)
{
	command("say " + item->name() + "﹐請拿好。");
	::deliver_merchandise(customer, item);
}
