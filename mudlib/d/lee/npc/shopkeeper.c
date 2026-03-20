// NPC: /d/lee/npc/shopkeeper.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("雜貨商", ({"shopkeeper", "merchant"}));
	set_race("human");
	set_class("commoner");
	set_level(6);

	set("age", 55);
	set("gender", "male");
	set("long",
		"一個頭髮花白的老漢﹐穿著一件打了補丁的粗布衣裳﹐笑呵呵\n"
		"地坐在貨架後面。他是村裡唯一的雜貨商﹐靠著這間小舖子維持生\n"
		"計。你可以用 list 看看有什麼﹐用 buy 來買。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"雜貨商笑道﹕客官隨便看看﹐都是實用的東西。\n",
		"雜貨商嘆了口氣﹕這年頭生意不好做啊。\n",
	}));
	set("merchandise", ([
		__DIR__"obj/tofu" : 10,
		__DIR__"obj/hoe" : 80,
	]));

	setup();
	carry_money("coin", 40);
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
}

int accept_fight(object ob)
{
	do_chat("雜貨商連忙擺手道﹕大俠饒命﹐小的只是個賣貨的﹗\n");
	return 0;
}

void deliver_merchandise(object customer, mixed item)
{
	command("say " + item->name() + "﹐拿好嘍。");
	::deliver_merchandise(customer, item);
}
