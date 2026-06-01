// teaman.c -- 衛國茶寮的茶博士（F_VENDOR 兼賣過往行旅的茶食點心與趕路乾糧﹐
//             純買賣 + 本地閒談）。不接任務、不交物、不動任何旗標。

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

int do_ask(string arg);

void create()
{
	set_name("茶博士", ({ "teaman", "tea master", "weiguo_teaman" }) );
	set("nickname", "茶博士");
	set_race("human");
	set_class("commoner");
	set_level(4);

	set("age", 41);
	set("gender", "male");
	set("long",
		"一個爽利的本鎮生意人﹐提著一把長嘴銅壺在桌間穿梭續\n"
		"水﹐臂上搭著塊白布巾﹐一面斟茶一面笑呵呵地搭話。這茶寮傍\n"
		"著市集﹐一半做的是趕集吃茶的營生﹐一半擺著茶食乾糧——歇腳\n"
		"的、出鎮的都用得著。你可以用 list 看他賣些什麼﹐用 buy 向\n"
		"他買東西。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"茶博士提著長嘴銅壺﹐隔著兩張桌子遠遠一注﹐滾水不偏不倚落進茶碗裡﹐引得茶客喝采。\n",
		"茶博士一面替客人續水﹐一面道﹕趕集吃茶歇歇腳﹐出鎮的客官多帶些點心乾糧﹐長路上墊墊飢。\n",
		"茶博士嘆道﹕咱這衛國鎮僻在邊縣﹐生意慢﹐圖個守著這一寮茶香、滿堂的閒話﹐自在罷了。\n",
	}));
	// 衛國茶寮兼賣行旅的茶食點心與趕路乾糧﹐沿用既有的乾糧吃食與傷藥物件販售。
	set("merchandise", ([
		"/obj/food/mooncake" : 28,
		"/obj/food/dumpling" : 35,
		"/obj/food/ricedough" : 45,
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
		return notify_fail("你想問這茶博士些甚麼﹖（試試 ask teaman about 衛國鎮）\n");

	if( arg == "teaman about 衛國鎮"
	||  arg == "teaman about 茶寮"
	||  arg == "teaman about 鎮"
	||  arg == "teaman about 衛國"
	||  arg == "teaman about weiguo" ) {
		do_chat(({
			(: command, "say 客官是頭一回逛咱這衛國鎮罷﹖咱這小鎮偏在邊縣﹐早年戍邊的軍屯﹐如今只剩這一鎮安生的市井人家。這茶寮便是鎮民會友閒談、客商話別的去處﹐茶食乾糧也都備著。客官坐下吃盞釅茶罷。" :),
			(: command, "say 客官若得閒﹐市集東邊是衛國客棧﹐東北炒米坊焙的炒米茶最是地道﹐場南石徑下去是鎮口的老古井﹐那井水甜得很。都去瞧瞧﹐圖個閒散自在。" :),
		}));
		return 1;
	}

	return notify_fail("茶博士爽利地一笑﹕客官要買些甚麼﹐只管 list 來瞧。\n");
}

int accept_fight(object ob)
{
	do_chat("茶博士連忙陪笑﹕客官有話好說﹗咱一個本分的生意人哪﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
