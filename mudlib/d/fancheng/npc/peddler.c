// peddler.c -- 海味雜貨鋪的老闆（F_VENDOR 販售既有的乾糧吃食與傷藥）

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("雜貨鋪老闆", ({ "peddler", "vendor", "shopkeeper" }) );
	set_race("human");
	set_class("commoner");
	set_level(4);

	set("age", 48);
	set("gender", "male");
	set("long",
		"一個精明的本地生意人﹐裹著件半舊的短褐﹐袖口捲得老高﹐\n"
		"露出曬得黝黑的手臂。他守著自家塞得滿滿的雜貨鋪﹐見了客\n"
		"人便堆起一臉的笑。你可以用 list 看他賣些什麼﹐用 buy 向他\n"
		"買東西。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"雜貨鋪老闆撥著算盤﹐笑瞇瞇地招呼道﹕客官要點什麼﹖行船趕路的物事﹐小店一應俱全﹗\n",
		"雜貨鋪老闆一面理著貨架﹐一面道﹕出海的客官﹐多帶些乾糧傷藥﹐這海上可不比陸地哩。\n",
		"雜貨鋪老闆數落道﹕這海風一颳﹐貨色潮得快﹐小本生意﹐難做喲。\n",
	}));
	// 港城雜貨鋪﹐沿用既有的乾糧吃食與傷藥物件販售。
	set("merchandise", ([
		"/obj/food/manto" : 60,
		"/obj/food/ricedough" : 50,
		"/obj/food/pork" : 30,
		"/obj/food/mooncake" : 30,
		"/obj/medication/boar_berry" : 10,
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
	do_chat("雜貨鋪老闆雙手叉腰﹐高聲嚷道﹕光天化日的﹐你想幹什麼﹖衛兵所就在街對面哪﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
