// innkeeper.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("客棧掌櫃", ({"innkeeper", "keeper"}));
	set_race("human");
	set_class("commoner");
	set_level(8);

	set("age", 40);
	set("gender", "male");
	set("long",
		"一個笑容可掬的胖掌櫃﹐圍著一條油膩膩的圍裙﹐手裡拎著一\n"
		"條抹布。他待人十分熱情﹐見人便笑臉相迎。你可以用 list 看看\n"
		"菜單﹐用 buy 跟他點菜。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"掌櫃笑呵呵地說﹕客倌﹐來點什麼﹖小店的肉包子可是一絕﹗\n",
		"掌櫃忙著擦桌子﹐嘴裡哼著小曲。\n",
		"掌櫃吆喝道﹕米酒﹗新鮮的米酒﹗\n",
	}));
	set("merchandise", ([
		__DIR__"obj/meat_bun" : 50,
		__DIR__"obj/rice_wine" : 50,
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
	do_chat("掌櫃連忙擺手道﹕客倌﹐小店可不興打架﹗\n");
	return 0;
}

void deliver_merchandise(object customer, mixed item)
{
	command("say " + item->name() + "來嘍﹗客倌慢用。");
	::deliver_merchandise(customer, item);
}
