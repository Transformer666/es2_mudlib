// teaman.c -- 甘泉茶館的茶博士（F_VENDOR 供應茶點吃食﹐純買賣 + 本地閒談）。
//             不接任務、不交物、不動任何旗標。

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

int do_ask(string arg);

void create()
{
	set_name("茶博士", ({ "teaman", "tea master", "louxian_teaman" }) );
	set("nickname", "茶博士");
	set_race("human");
	set_class("commoner");
	set_level(4);

	set("age", 39);
	set("gender", "male");
	set("long",
		"甘泉茶館的茶博士生得清瘦斯文﹐一身青布長衫漿洗得乾乾\n"
		"淨淨﹐提著一把長嘴銅壺﹐遠遠地便能把滾水準準地續進客人的\n"
		"茶盞裡。他煮的茶用的是縣北甘泉井的活水﹐茶湯格外清甘﹐又\n"
		"愛與茶客閒談縣裡縣外的見聞。你可以用 list 看茶館供應些什麼\n"
		"茶點﹐用 buy 向他點來嚐嚐。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"茶博士提著長嘴銅壺﹐手腕一抖﹐一道滾水準準地落進茶盞﹐滴水不濺。\n",
		"茶博士笑吟吟地道﹕客官嚐嚐這甘泉煮的清茶﹐配上一塊月餅﹐最是消閒。\n",
		"茶博士理著茶櫃上的茶葉罐道﹕咱這甘泉茶館﹐圖的就是一個地道的甘泉味兒。\n",
	}));
	// 甘泉茶館供應清茶配的茶點吃食﹐沿用既有的糕餅乾糧物件。
	set("merchandise", ([
		"/obj/food/mooncake" : 28,
		"/obj/food/ricedough" : 42,
		"/obj/food/manto" : 52,
	]));

	setup();
	carry_money("coin", 100);
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
		return notify_fail("你想問茶博士些甚麼﹖（試試 ask teaman about 婁縣）\n");

	if( arg == "teaman about 婁縣"
	||  arg == "teaman about 甘泉"
	||  arg == "teaman about 茶館"
	||  arg == "teaman about 茶"
	||  arg == "teaman about louxian" ) {
		do_chat(({
			(: command, "say 客官嚐得出罷﹖咱這茶用的是縣北甘泉井的活水﹐比尋常井水清甘十分﹐配什麼茶都出味﹐這便是咱甘泉茶館的招牌。" :),
			(: command, "say 客官是頭一回逛咱婁縣罷﹖出了茶館往東便是街心﹐街心北上去就是那口聞名的甘泉井﹐井北還有一座清幽的甘泉園﹐都值得一逛。客官慢慢吃茶。" :),
		}));
		return 1;
	}

	return notify_fail("茶博士正替客人續水﹐衝你溫文一笑﹕客官且坐下吃盞甘泉茶罷。\n");
}

int accept_fight(object ob)
{
	do_chat("茶博士忙不迭地擱下銅壺賠笑﹕客官息怒﹐有話坐下慢慢說﹐莫驚了滿堂的茶客。\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
