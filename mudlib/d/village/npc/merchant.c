// merchant.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("雜貨商人", ({"merchant", "shopkeeper"}));
	set_race("human");
	set_class("commoner");
	set_level(8);

	set("age", 45);
	set("gender", "male");
	set("long",
		"一個圓臉的中年男人﹐笑容可掬﹐身前擺著一個簡易的貨攤﹐\n"
		"上面擺著各種日常用品。他熱情地招呼著每一位路過的人﹐看起\n"
		"來生意做得有聲有色。你可以用 list 看看﹐用 buy 來買。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"雜貨商人吆喝道﹕乾糧火把﹐出門必備﹐便宜賣嘍﹗\n",
		"雜貨商人笑呵呵地說﹕客倌﹐看看有什麼需要的吧。\n",
		"雜貨商人整理了一下攤位上的貨物。\n",
	}));
	set("merchandise", ([
		__DIR__"obj/rope" : 30,
		__DIR__"obj/herb" : 50,
		STOCK_ITEM("ration") : 40,
		STOCK_ITEM("torch") : 20,
	]));

	setup();
	carry_money("coin", 100);
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
}

int accept_fight(object ob)
{
	do_chat("雜貨商人連忙擺手道﹕大俠饒命﹐小的只是個賣貨的﹗\n");
	return 0;
}

void deliver_merchandise(object customer, mixed item)
{
	command("say " + item->name() + "﹐拿好嘍﹐歡迎下次光臨。");
	::deliver_merchandise(customer, item);
}
