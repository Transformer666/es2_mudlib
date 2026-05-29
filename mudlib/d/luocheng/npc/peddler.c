// peddler.c -- 羅城雜貨鋪的老闆（F_VENDOR 販售既有的乾糧吃食與傷藥）

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("雜貨鋪老闆", ({ "luocheng peddler", "peddler", "shopkeeper" }) );
	set_race("human");
	set_class("commoner");
	set_level(4);

	set("age", 46);
	set("gender", "male");
	set("long",
		"一個八面玲瓏的本地生意人﹐裹著件乾淨的綢面短褂﹐見了\n"
		"客人便堆起一臉的笑﹐應對得格外殷勤周到。他守著自家收拾\n"
		"得齊整的雜貨鋪﹐專做這城裡官眷人家與謁選官人的生意。你\n"
		"可以用 list 看他賣些什麼﹐用 buy 向他買東西。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"雜貨鋪老闆撥著算盤﹐笑瞇瞇地招呼道﹕客官要點什麼﹖趕路謁選的物事﹐小店一應俱全﹗\n",
		"雜貨鋪老闆一面理著貨架﹐一面道﹕客官進京候缺﹐多帶些乾糧傷藥傍身﹐這一路上也好有個照應。\n",
		"雜貨鋪老闆陪笑道﹕咱們這城裡的貴人多﹐小本生意﹐圖的就是個和氣周到喲。\n",
	}));
	// 羅城雜貨鋪﹐沿用既有的乾糧吃食與傷藥物件販售。
	set("merchandise", ([
		"/obj/food/manto" : 60,
		"/obj/food/ricedough" : 50,
		"/obj/food/mooncake" : 30,
		"/obj/food/dumpling" : 50,
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
	do_chat("雜貨鋪老闆雙手叉腰﹐高聲嚷道﹕光天化日的﹐你想幹什麼﹖這可是天子腳下﹐城門守卒就在街口哪﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
