// peddler.c -- 水月村雜貨鋪的雜貨郎（F_VENDOR 販售既有的乾糧吃食與傷藥﹐
//              純買賣 + 本地閒談）。不接任務、不交物、不動任何旗標。

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

int do_ask(string arg);

void create()
{
	set_name("雜貨郎", ({ "peddler", "vendor", "shopkeeper", "shuiyue_peddler" }) );
	set("nickname", "雜貨郎");
	set_race("human");
	set_class("commoner");
	set_level(4);

	set("age", 48);
	set("gender", "male");
	set("long",
		"一個和氣的本村生意人﹐生得圓臉福相﹐裹著件漿洗得發白\n"
		"的短褐﹐成日價坐在櫃後搖著蒲扇﹐看溪水東流。他守著這谷裡\n"
		"唯一的雜貨鋪﹐村人過日子的零碎、行旅趕路的吃食傷藥﹐大半\n"
		"尋得著。你可以用 list 看他賣些什麼﹐用 buy 向他買東西。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"雜貨郎搖著蒲扇﹐笑呵呵地招呼道﹕客官要點什麼﹖過日子的零碎物事﹐小店大半尋得著哩。\n",
		"雜貨郎一面理著貨架﹐一面道﹕進山趕路的客官﹐多帶些乾糧傷藥﹐這谷外山路可不比村裡方便。\n",
		"雜貨郎嘆道﹕咱這水月村僻靜﹐生意慢﹐圖個守著這一溪好水﹐自在罷了。\n",
	}));
	// 水月村雜貨鋪﹐沿用既有的乾糧吃食與傷藥物件販售。
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
		return notify_fail("你想問這雜貨郎些甚麼﹖（試試 ask peddler about 水月村）\n");

	if( arg == "peddler about 水月村"
	||  arg == "peddler about 雜貨鋪"
	||  arg == "peddler about 村"
	||  arg == "peddler about 水月"
	||  arg == "peddler about shuiyue" ) {
		do_chat(({
			(: command, "say 客官是頭一回逛咱這水月村罷﹖小店是這谷裡唯一的鋪子了﹐過日子的零碎物事、趕路的乾糧傷藥﹐大半尋得著。" :),
			(: command, "say 村心北邊是福安客棧﹐東邊映月茶寮﹐東北上去是水月瀑布﹐東南柳堤下是浣月潭。客官慢慢逛便是。" :),
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
