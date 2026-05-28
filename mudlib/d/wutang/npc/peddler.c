// peddler.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("小販", ({ "peddler", "vendor" }) );
	set_race("human");
	set_class("commoner");
	set_level(3);

	set("age", 38);
	set("gender", "male");
	set("long",
		"一個精明的中年小販﹐眼睛滴溜溜地打量著每一個進門的客人。你\n"
		"可以用 list 看他賣些什麼﹐用 buy 向他買東西。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"小販撥著算盤﹐嘴裡念叨著﹕薄利多銷﹐薄利多銷 ...\n",
		"小販熱絡地招呼道﹕客官隨便看﹐想要什麼小店都有﹗\n",
		"小販拍著胸脯說道﹕我這兒的乾糧最是耐放﹐趕路的客官帶上些準沒錯﹗\n",
	}));
	// 雜貨鋪暫時只販售耐放的乾糧；日後可加入草鞋、油鹽等雜貨物件。
	// TODO: 增設草鞋、斗笠、火摺子等行旅雜貨 (需新建 obj 或沿用既有物件)。
	set("merchandise", ([
		"/obj/food/manto" : 60,
		"/obj/food/ricedough" : 40,
		"/obj/food/mooncake" : 20,
	]));

	setup();
	carry_money("coin", 150);
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
}

int accept_fight(object ob)
{
	do_chat("小販連忙護住貨架﹐賠笑道﹕和氣生財﹐和氣生財﹐客官別動氣呀﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
