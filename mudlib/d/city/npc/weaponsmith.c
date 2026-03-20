// NPC: /d/city/npc/weaponsmith.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("鐵匠", ({"weaponsmith", "blacksmith"}));
	set_race("human");
	set_class("commoner");
	set_level(18);

	set("age", 48);
	set("long",
		"一個膀大腰圓的鐵匠，裸著上身，露出結實的肌肉。他的雙\n"
		"手佈滿老繭，皮膚被爐火烤得黝黑發亮，一看就是個打鐵的好\n"
		"手。你可以用 list 看看他的貨品。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"鐵匠揮動大錘，叮叮噹噹地敲打著鐵砧上的兵器。\n",
		"鐵匠擦了擦汗說：想要好兵器？看看我打的刀劍！\n",
	}));
	set("merchandise", ([
		STOCK_WEAPON("short_sword") : 150,
		STOCK_WEAPON("long_sword")  : 300,
		STOCK_WEAPON("broad_blade") : 250,
		STOCK_WEAPON("pike")        : 200,
	]));

	setup();
	carry_money("coin", 400);
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
}

int accept_fight(object ob)
{
	do_chat("鐵匠怒道：找死！敢在老子的鋪子裡撒野！\n");
	return 1;
}
