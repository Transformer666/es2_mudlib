// shopman.c -- 文房鋪的鋪掌（F_VENDOR 兼賣文人案頭的茶食點心與趕路乾糧﹐
//              純買賣 + 本地閒談）。不接任務、不交物、不動任何旗標。

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

int do_ask(string arg);

void create()
{
	set_name("鋪掌", ({ "shopman", "vendor", "shopkeeper", "wenguo_shopman" }) );
	set("nickname", "鋪掌");
	set_race("human");
	set_class("commoner");
	set_level(4);

	set("age", 45);
	set("gender", "male");
	set("long",
		"一個爽利的本縣生意人﹐生得清瘦﹐裹著件漿洗得發白的長\n"
		"衫﹐成日價守著這文房鋪﹐一面替客人卷紙包墨﹐一面笑呵呵地\n"
		"搭話。鋪子一半賣讀書人的文房雜貨﹐一半擺著茶食乾糧——熬\n"
		"夜的、趕路的都用得著。你可以用 list 看他賣些什麼﹐用 buy\n"
		"向他買東西。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"鋪掌笑呵呵地招呼道﹕客官要點什麼﹖筆墨紙硯、茶食乾糧﹐小店都有哩。\n",
		"鋪掌一面替客人卷著一刀素紙﹐一面道﹕讀書熬夜傷神﹐多帶些點心墊墊﹐莫餓壞了身子。\n",
		"鋪掌嘆道﹕咱文國這小縣﹐別的不多﹐就是讀書人多、好筆好墨多﹐圖個斯文自在罷了。\n",
	}));
	// 文房鋪兼賣文人案頭的茶食點心與趕路乾糧﹐沿用既有的糕餅乾糧物件販售。
	set("merchandise", ([
		"/obj/food/mooncake" : 30,
		"/obj/food/manto" : 55,
		"/obj/food/ricedough" : 45,
		"/obj/food/dumpling" : 60,
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
		return notify_fail("你想問這鋪掌些甚麼﹖（試試 ask shopman about 文國）\n");

	if( arg == "shopman about 文國"
	||  arg == "shopman about 文房鋪"
	||  arg == "shopman about 縣"
	||  arg == "shopman about 文國縣"
	||  arg == "shopman about wenguo" ) {
		do_chat(({
			(: command, "say 客官是頭一回逛咱這文國縣罷﹖咱這小縣別的不多﹐就是讀書人多、好筆好墨多﹐人稱『翰墨之鄉』。小店筆墨紙硯、茶食乾糧都備著﹐客官慢慢逛便是。" :),
			(: command, "say 大街東邊是天風客棧﹐東南文瀾茶肆﹐西北制筆作坊﹔往北翰墨廣場﹐廣場東邊松煙墨坊﹐西邊一道月洞門進去是墨池小園。客官得空都去瞧瞧。" :),
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
