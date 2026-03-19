// flowergirl.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("賣花姑娘", ({"flowergirl", "girl"}));
	set_race("human");
	set_class("commoner");
	set_level(3);

	set("age", 16);
	set("long",
		"一個清秀可人的少女﹐穿著一件碎花布衣裳﹐烏黑的長髮上別\n"
		"著一朵小白花。她挎著一隻竹籃﹐裡面裝滿了各色鮮花﹐笑盈盈\n"
		"地向過路的人兜售。你可以用 list 看看﹐用 buy 來買。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"賣花姑娘笑吟吟地說﹕客倌﹐買束花吧﹐又香又好看。\n",
		"賣花姑娘哼著小曲﹐手指靈巧地編著花環。\n",
		"賣花姑娘說道﹕百花村的花可是遠近聞名的呢﹗\n",
	}));
	set("merchandise", ([
		__DIR__"obj/flower_bundle" : 50,
		__DIR__"obj/wreath" : 20,
	]));

	setup();
	carry_money("coin", 30);
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
}

int accept_fight(object ob)
{
	do_chat("賣花姑娘嚇得花容失色﹐連連後退。\n");
	return 0;
}

void deliver_merchandise(object customer, mixed item)
{
	command("say 給你﹐" + item->name() + "﹐祝你好運﹗");
	::deliver_merchandise(customer, item);
}
