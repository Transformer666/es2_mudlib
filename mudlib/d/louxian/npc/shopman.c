// shopman.c -- 婁縣雜貨鋪的雜貨郎（F_VENDOR 販售既有的乾糧吃食與傷藥﹐
//              純買賣 + 本地閒談）。不接任務、不交物、不動任何旗標。

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

int do_ask(string arg);

void create()
{
	set_name("雜貨郎", ({ "shopman", "peddler", "vendor", "louxian_shopman" }) );
	set("nickname", "雜貨郎");
	set_race("human");
	set_class("commoner");
	set_level(4);

	set("age", 45);
	set("gender", "male");
	set("long",
		"一個和氣的本縣生意人﹐生得圓臉福相﹐裹著件漿洗得發白\n"
		"的短褐﹐成日價坐在櫃後搖著蒲扇﹐慢條斯理地候著生意。他守\n"
		"著這婁縣城裡唯一的雜貨鋪﹐縣人過日子的零碎、行旅趕路的吃\n"
		"食傷藥﹐大半尋得著。你可以用 list 看他賣些什麼﹐用 buy 向他\n"
		"買東西。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"雜貨郎搖著蒲扇﹐笑呵呵地招呼道﹕客官要點什麼﹖過日子的零碎物事﹐小店大半尋得著哩。\n",
		"雜貨郎一面理著貨架﹐一面道﹕進山趕路的客官﹐多帶些乾糧傷藥﹐這縣外山路可不比縣裡方便。\n",
		"雜貨郎嘆道﹕咱這婁縣僻靜﹐生意慢﹐圖個守著這一口甘泉﹐自在罷了。\n",
	}));
	// 婁縣雜貨鋪﹐沿用既有的乾糧吃食與傷藥物件販售。
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
		return notify_fail("你想問這雜貨郎些甚麼﹖（試試 ask shopman about 婁縣）\n");

	if( arg == "shopman about 婁縣"
	||  arg == "shopman about 雜貨鋪"
	||  arg == "shopman about 縣"
	||  arg == "shopman about 甘泉"
	||  arg == "shopman about louxian" ) {
		do_chat(({
			(: command, "say 客官是頭一回逛咱這婁縣罷﹖小店是這縣裡唯一的鋪子了﹐過日子的零碎物事、趕路的乾糧傷藥﹐大半尋得著。" :),
			(: command, "say 出了巷子往西南就回街心了﹐街心東邊是甘泉客棧﹐西邊甘泉茶館﹐往北上去是甘泉井﹐井北還有座甘泉園。客官慢慢逛便是。" :),
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
