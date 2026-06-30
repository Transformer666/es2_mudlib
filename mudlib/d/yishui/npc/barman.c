// barman.c -- 羿水酒館掌櫃：賣酒食魚鮮的 F_VENDOR。
//   小魚村酒館掌櫃，原是村裡打魚的漢子，腿腳不便後盤下這爿小酒館。供應自家
//   釀的村醪米酒(複用 /d/longan/obj/rice_wine)、鹽烤河魚與尋常吃食。
//   純賣食/閒談，不發物、不動旗標、無 do_ask 任務鏈。
//
// 【runtime 鐵則】NPC 有自訂 init()(add_action do_vendor_list "list")；招呼 do_chat
//   一律加 interactive(this_player()) 護衛（lesson #14：防 say-storm）。不 replace_program。

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("酒館掌櫃", ({ "barman", "yishui_barman", "zhanggui" }) );
	set("nickname", "掌櫃");
	set_race("human");
	set_class("commoner");
	set_level(4);

	set("age", 51);
	set("gender", "male");
	set("long",
		"一個圍著油布圍裙的精瘦漢子﹐臉膛曬得黧黑﹐眼角堆著常年\n"
		"在水上眯眼看光的細紋。他原也是村裡打魚的好手﹐後來一條腿\n"
		"在水上落下了病﹐使不上勁了﹐才盤下這爿臨河的小酒館﹐守著\n"
		"一甕米酒、一盆炭火過活。你可以用 list 看櫃上有些什麼酒食﹐\n"
		"用 buy 向他沽來。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"掌櫃在灶邊翻著烤魚﹐油星濺起﹐他眯眼笑道﹕客官嚐嚐這羿水的河鮮﹐保管比城裡的鮮甜。\n",
		"掌櫃拿粗布抹著碗﹐自言自語﹕這村醪是用河上的活水釀的﹐勁兒不大﹐後勁卻足﹐莫貪杯哪。\n",
		"掌櫃望了望門外的煙波﹐歎道﹕又起風了﹐出船的那幾個﹐可得早些回來纔好。\n",
	}));
	// 羿水酒館供應自釀村醪米酒、本地鹽烤河魚、現撈小魚﹐另搭尋常的饅頭包子。
	// 米酒複用龍安水鄉米酒(F_VENDOR 賣酒自動以 /obj/bottle 盛裝交付)。
	set("merchandise", ([
		"/d/longan/obj/rice_wine" : 1,          // 村醪米酒(液體，自動瓶裝)
		__DIR__"obj/grilled_fish" : 1,          // 本地鹽烤河魚
		"/obj/food/fish" : 30,                   // 現撈小魚(複用既有)
		"/obj/food/manto" : 40,
		"/obj/food/dumpling" : 40,
	]));

	setup();
	carry_money("coin", 100);
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");

	// 招呼一律加 interactive(this_player()) 護衛——只對真人，防 NPC 互觸成洗版(lesson #14)。
	if( this_player() && interactive(this_player()) && !is_fighting() )
		do_chat(({
			"掌櫃抬頭眯眼一笑﹕這位" + this_player()->rank("respectful") + "﹐打魚的累了罷﹖坐下沽兩碗村醪、烤尾鮮魚﹐歇一歇腳。\n",
		}));
}

int accept_fight(object ob)
{
	do_chat("掌櫃一瘸一拐地往灶後躲﹐賠笑道﹕客官息怒﹗小店窮得很﹐酒儘管喝﹐可別動手哇﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
