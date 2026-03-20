// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("鐵匠", ({"weaponsmith", "smith", "tiejiang"}));
	set_race("human");
	set_class("commoner");
	set_level(12);

	set("age", 40);
	set("gender", "male");
	set("long",
		"一個膀大腰圓的鐵匠，結實的臂膀上肌肉隆起，身上穿著一件\n"
		"厚實的皮圍裙。店鋪後方不時傳來叮噹的打鐵聲。他出售各式兵\n"
		"器。你可以用 list 看看他的兵器。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"鐵匠擦了擦額頭上的汗：好鋼要經千錘百煉，方能鑄成利刃。\n",
		"鐵匠拿起一把新打好的長劍端詳：嗯，這把劍的火候剛剛好。\n",
		"鐵匠對你說道：要買兵器就來我這，保證都是真材實料。\n",
	}));
	set("merchandise", ([
		STOCK_WEAPON("longsword") : 15,
		STOCK_WEAPON("broadsword") : 15,
		STOCK_WEAPON("dagger") : 20,
		STOCK_WEAPON("staff") : 10,
	]));

	set_attr("str", 17);
	set_attr("con", 16);
	set_skill("unarmed", 25);

	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
	carry_money("coin", 400);
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
}

int accept_fight(object ob)
{
	do_chat("鐵匠冷冷地說：我這兒是做買賣的，不是比武場。\n");
	return 0;
}
