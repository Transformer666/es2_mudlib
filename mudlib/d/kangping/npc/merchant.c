// NPC: /d/kangping/npc/merchant.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("貨郎", ({"merchant", "peddler"}));
	set_race("human");
	set_class("commoner");
	set_level(7);

	set("age", 40);
	set("gender", "male");
	set("long",
		"一個挑著擔子走村串戶的貨郎﹐皮膚黝黑﹐笑容憨厚。他的貨\n"
		"擔裡裝著各種日常雜貨﹐雖然都是些不值錢的東西﹐但對村民來說\n"
		"卻是必需品。你可以用 list 看看有什麼﹐用 buy 來買。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"貨郎吆喝道﹕針頭線腦﹐油鹽醬醋﹐應有盡有嘍﹗\n",
		"貨郎擦了擦汗﹐說道﹕走了一天的路﹐總算到村子了。\n",
	}));
	set("merchandise", ([
		__DIR__"obj/straw_sandal" : 20,
		__DIR__"obj/herb_tea" : 50,
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
	do_chat("貨郎連忙擺手道﹕大俠饒命﹐小的只是個賣貨的﹗\n");
	return 0;
}

void deliver_merchandise(object customer, mixed item)
{
	command("say " + item->name() + "﹐拿好嘍。");
	::deliver_merchandise(customer, item);
}
