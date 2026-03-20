// NPC: /d/chixiao/npc/merchant.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("雜貨攤主", ({"merchant", "shopkeeper"}));
	set_race("human");
	set_class("commoner");
	set_level(7);

	set("age", 42);
	set("gender", "male");
	set("long",
		"一個精瘦的中年男人﹐眼珠子骨碌碌地轉著﹐一看就是個精明\n"
		"的生意人。他在這偏僻的村子裡賣些雜貨﹐雖然東西不多﹐但價\n"
		"格倒也公道。你可以用 list 看看有什麼﹐用 buy 來買。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"攤主吆喝道﹕符紙靈酒﹐驅邪避凶﹐走過路過不要錯過﹗\n",
		"攤主壓低聲音說﹕聽說村子北邊的許願池鬧鬼﹐要買符紙嗎﹖\n",
	}));
	set("merchandise", ([
		__DIR__"obj/talisman" : 30,
		__DIR__"obj/spirit_wine" : 50,
	]));

	setup();
	carry_money("coin", 80);
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
}

int accept_fight(object ob)
{
	do_chat("攤主連忙擺手道﹕大俠饒命﹐小的只是個賣貨的﹗\n");
	return 0;
}

void deliver_merchandise(object customer, mixed item)
{
	command("say " + item->name() + "﹐拿好嘍。");
	::deliver_merchandise(customer, item);
}
