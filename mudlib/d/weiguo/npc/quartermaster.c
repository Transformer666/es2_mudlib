// NPC: /d/weiguo/npc/quartermaster.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("軍需官", ({"quartermaster", "officer"}));
	set_attr("str", 16);
	set_attr("con", 16);
	set_race("human");
	set_class("commoner");
	set_level(14);

	set_skill("sword", 40);
	set_skill("unarmed", 30);

	set("age", 42);
	set("gender", "male");
	set("long",
		"一位身材魁梧的軍需官，穿著整齊的軍服，正在清點營房裡的物\n"
		"資。他做事一絲不苟，每一件軍需品都要親自過目。你可以用 list\n"
		"看看他手頭有什麼可以交易的軍需品。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"軍需官對照著帳冊清點物資，嘴裡唸唸有詞。\n",
		"軍需官皺眉道：這批箭矢的數目又對不上了……\n",
	}));
	set("merchandise", ([
		STOCK_WEAPON("broadsword") : 10,
		STOCK_WEAPON("pike") : 10,
		STOCK_ARMOR("cloth") : 20,
	]));

	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
	carry_object(STOCK_WEAPON("broadsword"))->wield();
	carry_money("coin", 300);
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
}

int accept_fight(object ob)
{
	do_chat("軍需官冷聲道：這裡是軍營重地，動手的話後果自負！\n");
	return 0;
}
