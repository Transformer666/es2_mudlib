// tea_lady.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("茶娘", ({"tea_lady", "tea lady"}));
	set_race("human");
	set_class("commoner");
	set_level(5);

	set("age", 35);
	set("long",
		"一個面容和善的中年婦人﹐穿著素雅的碎花布衫﹐頭上包著一\n"
		"塊藍色頭巾。她手腳麻利地沏著茶﹐不時招呼著進門的客人。你可\n"
		"以用 list 看看菜單﹐用 buy 跟她買東西。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"茶娘笑著招呼道﹕客倌﹐來杯茶吧﹗本店的清月綠茶可是一絕﹗\n",
		"茶娘忙碌地擦拭著桌子﹐嘴裡哼著小曲兒。\n",
		"茶娘說道﹕桂花糕剛出爐的﹐趁熱吃才香呢。\n",
	}));
	set("merchandise", ([
		__DIR__"obj/green_tea" : 30,
		__DIR__"obj/rice_cake" : 30,
		__DIR__"obj/dried_fish" : 50,
	]));

	setup();
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
}

int accept_fight(object ob)
{
	do_chat("茶娘連忙擺手道﹕客倌﹐這是茶樓﹐可不興打架呀﹗\n");
	return 0;
}

void deliver_merchandise(object customer, mixed item)
{
	command("say " + item->name() + "﹖好嘞﹐馬上來﹗");
	::deliver_merchandise(customer, item);
}
