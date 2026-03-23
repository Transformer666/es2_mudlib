// NPC: /d/kangping/npc/blacksmith.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("鐵匠", ({"blacksmith", "smith"}));
	set_race("human");
	set_class("commoner");
	set_level(10);

	set("age", 45);
	set("gender", "male");
	set("long",
		"一個膀大腰圓的中年漢子﹐裸著上身﹐皮膚被爐火烤得黝黑發亮。\n"
		"他的雙臂粗壯有力﹐手上佈滿老繭和燙傷的疤痕。雖然手藝算不上\n"
		"精巧﹐但打出來的刀具倒也結實耐用。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"鐵匠擦了擦額頭的汗珠﹐又掄起了鐵錘。\n",
		"鐵匠往爐中添了幾塊炭﹐火苗呼地一下竄了上來。\n",
	}));
	set("merchandise", ([
		__DIR__"obj/hunting_knife" : 20,
		"/obj/area/obj/blade"     : 10,
		"/obj/area/obj/staff"     : 10,
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
	do_chat("鐵匠揮了揮鐵錘﹐說道﹕莫要在我這棚子裡動手﹗\n");
	return 0;
}

void deliver_merchandise(object customer, mixed item)
{
	command("say " + item->name() + "﹐拿去吧。");
	::deliver_merchandise(customer, item);
}
