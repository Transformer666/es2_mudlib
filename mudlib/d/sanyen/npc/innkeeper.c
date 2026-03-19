// innkeeper.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("客店老闆", ({"innkeeper", "boss"}));
	set_race("human");
	set_class("commoner");
	set_level(8);

	set("age", 55);
	set("long",
		"一個瘦小的老頭﹐頭髮已經花白了。他經營這間小客店多年﹐\n"
		"生意一直不好﹐但也沒有別的營生﹐只好繼續撐著。你可以用 list\n"
		"看看有什麼﹐用 buy 來買。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"老闆打了個哈欠﹐有氣無力地說﹕客倌﹐要吃點啥﹖\n",
		"老闆嘆道﹕生意越來越難做了﹐都怪山上那幫強盜。\n",
	}));
	set("merchandise", ([
		__DIR__"obj/incense" : 50,
		__DIR__"obj/prayer_beads" : 10,
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
	do_chat("老闆嚇得連連擺手﹕別打別打﹐小老兒可經不起折騰。\n");
	return 0;
}

void deliver_merchandise(object customer, mixed item)
{
	command("say " + item->name() + "﹐給你。");
	::deliver_merchandise(customer, item);
}
