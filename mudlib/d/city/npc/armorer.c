// NPC: /d/city/npc/armorer.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("甲冑匠", ({"armorer", "armor smith"}));
	set_race("human");
	set_class("commoner");
	set_level(15);

	set("age", 52);
	set("long",
		"一個沉穩的老匠人，鬢髮斑白但精神矍鑠。他正在仔細地\n"
		"修補一副鎧甲上的鱗片，手法嫻熟而精準。\n"
		"你可以用 list 看看他的貨品。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"甲冑匠仔細地檢查著一副護甲的每一處接縫。\n",
		"甲冑匠說道：好的護甲能救你一命，可別不捨得花錢。\n",
	}));
	set("merchandise", ([
		STOCK_ARMOR("cloth")       : 50,
		STOCK_ARMOR("leather")     : 150,
		STOCK_ARMOR("iron_armor")  : 400,
	]));

	setup();
	carry_money("coin", 300);
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
}

int accept_fight(object ob)
{
	do_chat("甲冑匠冷哼一聲：老夫年紀雖大，可不是好欺負的！\n");
	return 1;
}
