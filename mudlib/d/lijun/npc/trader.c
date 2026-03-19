// trader.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("行商", ({"trader", "merchant"}));
	set_attr("str", 12);
	set_attr("con", 14);
	set_attr("dex", 16);
	set_race("human");
	set_class("commoner");
	set_level(10);

	set("age", 40);
	set("long",
		"一個精明幹練的行商﹐穿著一身半舊的藏青色長衫﹐肩上搭著\n"
		"一條汗巾。他的攤位上擺著斗笠、竹竿之類的雜貨﹐不時吆喝幾\n"
		"聲招攬生意。你可以用 list 看看他賣些什麼﹐用 buy 購買。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"行商吆喝道﹕走過路過不要錯過﹗上好的斗笠﹐擋風遮雨﹗\n",
		"行商說道﹕這竹竿可是南邊竹林裡精挑細選的﹐結實得很﹗\n",
		"行商嘆道﹕如今走南闖北不容易﹐河匪越來越猖獗了。\n",
	}));
	set("merchandise", ([
		__DIR__"obj/straw_hat" : 20,
		__DIR__"obj/bamboo_pole" : 20,
		__DIR__"obj/dried_fish" : 50,
	]));

	setup();
	carry_money("coin", 200);
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
}

void deliver_merchandise(object customer, mixed item)
{
	command("say " + item->name() + "﹐好眼光﹗給你﹗");
	::deliver_merchandise(customer, item);
}
