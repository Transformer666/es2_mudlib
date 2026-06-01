// shopman.c -- 香貨鋪的鋪掌（F_VENDOR 兼賣香客案頭的茶食點心與趕路乾糧﹐
//              純買賣 + 本地閒談）。不接任務、不交物、不動任何旗標。

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

int do_ask(string arg);

void create()
{
	set_name("鋪掌", ({ "shopman", "vendor", "shopkeeper", "ziyan_shopman" }) );
	set("nickname", "鋪掌");
	set_race("human");
	set_class("commoner");
	set_level(4);

	set("age", 44);
	set("gender", "male");
	set("long",
		"一個爽利的本鎮生意人﹐生得圓臉福相﹐裹著件被香氣熏得\n"
		"暖融融的短褐﹐成日守著這香貨鋪﹐一面替客人秤香包點心﹐一\n"
		"面笑呵呵地搭話。鋪子一半賣香客愛討的香貨雜物﹐一半擺著茶\n"
		"食乾糧——泡溫泉的、趕路的都用得著。你可以用 list 看他賣些\n"
		"什麼﹐用 buy 向他買東西。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"鋪掌笑呵呵地招呼道﹕客官要點什麼﹖線香香草、茶食乾糧﹐小店都有哩。\n",
		"鋪掌一面替客人秤著一束線香﹐一面道﹕逛鎮泡湯傷神﹐多帶些點心墊墊﹐莫餓壞了身子。\n",
		"鋪掌嘆道﹕咱這紫煙鎮僻靜﹐生意慢﹐圖個守著這一眼好溫泉、滿鎮的好香﹐自在罷了。\n",
	}));
	// 香貨鋪兼賣香客案頭的茶食點心與趕路乾糧﹐沿用既有的乾糧吃食與傷藥物件販售。
	set("merchandise", ([
		"/obj/food/manto" : 55,
		"/obj/food/ricedough" : 45,
		"/obj/food/mooncake" : 28,
		"/obj/medication/boar_berry" : 10,
	]));

	setup();
	carry_money("coin", 120);
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
	add_action("do_ask", "ask");
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這鋪掌些甚麼﹖（試試 ask shopman about 紫煙鎮）\n");

	if( arg == "shopman about 紫煙鎮"
	||  arg == "shopman about 香貨鋪"
	||  arg == "shopman about 鎮"
	||  arg == "shopman about 紫煙"
	||  arg == "shopman about ziyan" ) {
		do_chat(({
			(: command, "say 客官是頭一回逛咱這紫煙鎮罷﹖咱這小鎮倚著一眼溫泉過活﹐湯氣裊裊﹐晨昏一映便泛出淡淡的紫煙﹐鎮子的名號就是從這兒來的。小店香貨雜物、茶食乾糧都備著﹐客官慢慢逛便是。" :),
			(: command, "say 鎮心北邊是紫煙小棧﹐東邊煮泉茶寮﹐南面石階下去是紫煙溫泉﹐西北石階上去是焙香人歇腳的沉香小亭。客官得空都去瞧瞧﹐泡個溫泉最是舒坦。" :),
		}));
		return 1;
	}

	return notify_fail("鋪掌爽利地一笑﹕客官要買些甚麼﹐只管 list 來瞧。\n");
}

int accept_fight(object ob)
{
	do_chat("鋪掌連忙陪笑﹕客官有話好說﹗咱一個本分的生意人哪﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
