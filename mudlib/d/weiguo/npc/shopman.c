// shopman.c -- 衛國雜貨鋪的雜貨郎（F_VENDOR 販售既有的乾糧吃食與傷藥﹐
//              純買賣 + 本地閒談）。不接任務、不交物、不動任何旗標。

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

int do_ask(string arg);

void create()
{
	set_name("雜貨郎", ({ "shopman", "vendor", "shopkeeper", "weiguo_shopman" }) );
	set("nickname", "雜貨郎");
	set_race("human");
	set_class("commoner");
	set_level(4);

	set("age", 46);
	set("gender", "male");
	set("long",
		"一個和氣的本鎮生意人﹐生得圓臉福相﹐裹著件漿洗得發白\n"
		"的短褐﹐成日價坐在櫃後搖著蒲扇﹐看街上趕集的人來人往。他\n"
		"守著這市集邊的雜貨鋪﹐鎮人過日子的零碎、行旅趕路的吃食傷\n"
		"藥﹐大半尋得著。你可以用 list 看他賣些什麼﹐用 buy 向他買東西。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"雜貨郎搖著蒲扇﹐笑呵呵地招呼道﹕客官要點什麼﹖過日子的零碎物事﹐小店大半尋得著哩。\n",
		"雜貨郎一面理著貨架﹐一面道﹕出鎮趕路的客官﹐多帶些乾糧傷藥﹐這邊縣外頭的長路可不比鎮裡方便。\n",
		"雜貨郎嘆道﹕咱這衛國鎮偏在邊縣﹐生意慢﹐圖個守著這一鎮安生﹐自在罷了。\n",
	}));
	// 衛國雜貨鋪﹐沿用既有的乾糧吃食與傷藥物件販售。
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
		return notify_fail("你想問這雜貨郎些甚麼﹖（試試 ask shopman about 衛國鎮）\n");

	if( arg == "shopman about 衛國鎮"
	||  arg == "shopman about 雜貨鋪"
	||  arg == "shopman about 鎮"
	||  arg == "shopman about 衛國"
	||  arg == "shopman about weiguo" ) {
		do_chat(({
			(: command, "say 客官是頭一回逛咱這衛國鎮罷﹖咱這小鎮偏在邊縣﹐早年是戍邊的軍屯關隘﹐如今刀兵入庫﹐只剩這一鎮安居的市井人家。小店過日子的零碎、趕路的乾糧傷藥﹐大半尋得著。客官慢慢逛便是。" :),
			(: command, "say 市集東邊是衛國客棧﹐西北一爿茶寮﹐東北是炒米坊﹐場南石徑下去是鎮口的老古井。客官得空都去瞧瞧﹐出鎮在即﹐莫忘了帶足乾糧。" :),
		}));
		return 1;
	}

	return notify_fail("雜貨郎搖著蒲扇憨憨一笑﹕客官要買些甚麼﹐只管 list 來瞧。\n");
}

int accept_fight(object ob)
{
	do_chat("雜貨郎連忙縮手陪笑﹕客官有話好說﹗咱一個本分的生意人哪﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
