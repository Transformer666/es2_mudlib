// peddler.c -- 海味雜貨鋪的老闆（F_VENDOR 販售既有的乾糧吃食與傷藥）；
//              兼檒城非戰鬥支線「望安港的斷龍骨」的線索人之一（識貨的行腳商）。
//
// 任務銜接（旗標皆存在玩家身上，支線由 /d/fancheng/npc/boatman.c 開啟）：
//   須先接任務 (quest/fancheng_sea==1) ﹐ask peddler about 龍骨 ->
//     老闆道出何處有堪作船骨的好松木（老松林一帶的直紋松）。
//     若這條線索未記過﹐則設 quest/fancheng_sea_wood = 1。
//   未接任務 / 已記過 / 已完成支線：只作對應的閒談﹐不重複記旗標。
//
// 注意：本 NPC 不開啟任務、不領賞、不交付物件﹔線索純以對話交付。
//       既有的 list / buy 販售功能一仍其舊。

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

int do_ask(string arg);

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
		"人便堆起一臉的笑。早年他販貨走南闖北﹐木料行情也頗識得\n"
		"幾分。你可以用 list 看他賣些什麼﹐用 buy 向他買東西﹐\n"
		"或問問他﹕ask peddler about 龍骨。\n");
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
	add_action("do_ask", "ask");
}

int do_ask(string arg)
{
	object me = this_player();
	int q;

	if( !arg || (arg != "peddler about 龍骨"
		&&   arg != "vendor about 龍骨"
		&&   arg != "shopkeeper about 龍骨"
		&&   arg != "peddler about 木料"
		&&   arg != "peddler about 船料"
		&&   arg != "peddler about 木牌"
		&&   arg != "peddler about 修船"
		&&   arg != "peddler about keel"
		&&   arg != "peddler about wood") )
		return notify_fail("你想問這位老闆甚麼﹖（試試 ask peddler about 龍骨）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("雜貨鋪老闆正撥著算盤核帳﹐沒空理你。\n");

	q = me->query("quest/fancheng_sea");

	// 未接任務：含糊帶過，順道把人引向船塢的老船匠
	if( q < 1 ) {
		do_chat((: command,
			"say 龍骨﹖客官問這個做甚﹖小店是賣雜貨的﹐這要打聽船料﹐還是往港邊船塢尋那老船匠去。" :));
		return 1;
	}

	// 已記過此線索（或支線已完成）：只重述，不再記旗標
	if( q >= 2 || me->query("quest/fancheng_sea_wood") ) {
		do_chat((: command,
			"say 好松木麼﹖方才不對客官說了﹖老松林一帶的直紋松最是耐用﹐憑著官中的領料木牌﹐去那邊料場支領便是。" :));
		return 1;
	}

	// 任務進行中、此線索未記過：道出木料來路，記下線索旗標
	do_chat(({
		(: command, "say 老船匠託客官打聽龍骨好料﹖嘿﹐這可問著行家了。小本買賣之前﹐我也曾販過幾年木料﹐這船骨的講究﹐略知一二。" :),
		(: command, "say 做龍骨﹐最要紋理筆直、堅韌耐蛀﹐尋常雜木可擔不起一船的脊樑。要我說﹐就數北邊老松林一帶的直紋老松最是頂用——那林子裡的松木長得慢﹐木質又密又韌﹐泡了海水也不易朽。" :),
		(: command, "say 只是那好料素歸官中料場掌著﹐外人買不著﹐得有衛兵所開的領料木牌方能去支。客官要替老船匠張羅﹐記著去衛兵所尋劉統領討面木牌﹐再回去回了老船匠便是。" :),
	}));
	// 線索確實道出後才記旗標（先確認上面未記過，故此處不會重複記）
	me->set("quest/fancheng_sea_wood", 1);
	return 1;
}

int accept_fight(object ob)
{
	do_chat("雜貨鋪老闆雙手叉腰﹐高聲嚷道﹕光天化日的﹐你想幹什麼﹖衛兵所就在街對面哪﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
