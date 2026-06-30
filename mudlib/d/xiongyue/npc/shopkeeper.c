// shopkeeper.c -- 山月小鋪的鋪主（F_VENDOR 販售既有的乾糧吃食與傷藥）
//
// 結構鏡 /d/zhaoyin/npc/peddler.c：F_VILLAGER + F_VENDOR，沿用既有的乾糧傷藥
// 物件販售，不主動鬥毆。供入熊月村後山獵獸者補給。

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("鋪主", ({ "shopkeeper", "vendor", "puzhu" }) );
	set_race("human");
	set_class("commoner");
	set_level(4);

	set("age", 47);
	set("gender", "male");
	set("long",
		"一個面容黧黑的山裡人﹐生得敦實﹐一雙手粗糙皴裂﹐盡是常\n"
		"年勞作的痕跡。他守著這村裡唯一的雜貨小鋪﹐話雖不多﹐見了\n"
		"客卻最是熱心﹐總勸進山的人多備些乾糧傷藥。你可以用 list 看\n"
		"他賣些什麼﹐用 buy 向他買東西。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"鋪主憨厚地笑道﹕客官是打山外來的罷﹖咱這山月小鋪﹐進山的乾糧傷藥還算齊全﹐多帶些不吃虧。\n",
		"鋪主一面理著貨架﹐一面低聲叮囑﹕後山那林子兇得很﹐熊羆山魈都有﹐沒個三五分本事﹐可別一個人往深裡闖。\n",
		"鋪主嘆道﹕咱這熊月村地僻人稀﹐一年也來不了幾個外鄉人﹐小本生意﹐圖個溫飽罷了。\n",
	}));
	// 山村雜貨鋪﹐沿用既有的乾糧吃食與傷藥物件販售(鏡 zhaoyin/peddler)。
	set("merchandise", ([
		"/obj/food/manto" : 60,
		"/obj/food/ricedough" : 48,
		"/obj/food/mooncake" : 30,
		"/obj/medication/boar_berry" : 12,
	]));

	setup();
	carry_money("coin", 100);
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
}

int accept_fight(object ob)
{
	do_chat("鋪主連忙縮手陪笑﹕客官有話好說﹗小本生意﹐求財不求氣哪﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
