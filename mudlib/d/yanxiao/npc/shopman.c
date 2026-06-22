// shopman.c -- 焱硝村中小店的店家（F_VENDOR 供應行旅補給）。
//              莽林偏村人煙稀少﹐穿林過路的客人多在此添些耐放口糧。
//              沿用既有乾糧食物物件﹐不另造物。

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("店家", ({ "shopman", "yanxiao_shopman", "keeper" }) );
	set("nickname", "店家");
	set_race("human");
	set_class("commoner");
	set_level(3);

	set("age", 52);
	set("gender", "male");
	set("long",
		"一個精瘦的中年店家﹐守著這莽林偏村裡唯一的一間小店過活。\n"
		"他臉上的皺紋裡都嵌著洗不淨的硫硝黃灰﹐渾濁的眼睛卻精明﹐見\n"
		"有客人進門便亮了起來。你可以用 list 看櫃上有些什麼﹐用 buy\n"
		"向他買些耐放的乾糧口糧﹐再上路趕程。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"店家撥著算盤﹐口中念叨﹕咱這偏村小店﹐一日也做不了幾筆生意囉 ...\n",
		"店家熱絡地招呼﹕客官是穿莽林過路的罷﹖添些乾糧炊餅﹐路上頂飢﹗\n",
		"店家壓低了聲音說﹕客官往北、往西那莽林深處可去不得﹐近來有夥盜匪落了草﹐專劫過路的孤客哩。\n",
	}));
	// 莽林偏村小店﹐只販售耐放的乾糧炊餅(沿用既有食物物件﹐不另造物)。
	set("merchandise", ([
		"/obj/food/manto" : 60,
		"/obj/food/ricedough" : 40,
		"/obj/food/mooncake" : 20,
	]));

	setup();
	carry_money("coin", 120);
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
}

int accept_fight(object ob)
{
	do_chat("店家連忙護住貨架賠笑﹕和氣生財﹗客官有話好說﹐別動手呀﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
