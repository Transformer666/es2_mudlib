// melon_farmer.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("瓜農", ({"melon_farmer", "farmer"}));
	set_race("human");
	set_class("commoner");
	set_level(5);

	set("age", 50);
	set("gender", "male");
	set("long",
		"一個皮膚黝黑的老農﹐戴著一頂破草帽﹐蹲在瓜田裡忙活。他\n"
		"種的西瓜又大又甜﹐在附近幾個村子都有名氣。你可以用 list 看\n"
		"看﹐用 buy 來買。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"瓜農拍了拍一個大西瓜﹐笑道﹕聽這聲音﹐準是個甜的﹗\n",
		"瓜農自言自語道﹕今年雨水充足﹐瓜長得好哇。\n",
	}));
	set("merchandise", ([
		__DIR__"obj/watermelon" : 50,
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
	do_chat("瓜農擺擺手道﹕我就是個種瓜的﹐別找我打架。\n");
	return 0;
}

void deliver_merchandise(object customer, mixed item)
{
	command("say 好咧﹐" + item->name() + "拿好﹗");
	::deliver_merchandise(customer, item);
}
