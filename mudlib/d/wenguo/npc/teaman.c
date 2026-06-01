// teaman.c -- 文瀾茶肆的茶博士（F_VENDOR 供應茶點吃食﹐純買賣 + 本地閒談）。
//             不接任務、不交物、不動任何旗標。

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

int do_ask(string arg);

void create()
{
	set_name("茶博士", ({ "teaman", "tea master", "wenguo_teaman" }) );
	set("nickname", "茶博士");
	set_race("human");
	set_class("commoner");
	set_level(4);

	set("age", 38);
	set("gender", "male");
	set("long",
		"文瀾茶肆的茶博士生得清瘦斯文﹐一身青布長衫漿洗得乾乾\n"
		"淨淨﹐提著一把長嘴銅壺﹐遠遠地便能把滾水準準地續進客人的\n"
		"茶盞裡。他在這文士雲集的茶肆裡跑堂多年﹐肚裡裝著縣中文壇\n"
		"的不少掌故﹐又愛湊趣與茶客評詩談墨。你可以用 list 看茶肆\n"
		"供應些什麼茶點﹐用 buy 向他點來嚐嚐。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"茶博士提著長嘴銅壺﹐手腕一抖﹐一道滾水準準地落進茶盞﹐滴水不濺。\n",
		"茶博士笑吟吟地道﹕客官嚐嚐這一盞﹐配上一碟桂花糕﹐邊吃邊看牆上的詩箋﹐最是消閒。\n",
		"茶博士湊到一桌正聯句的書生跟前﹐眯眼讀了讀﹐撫掌笑道﹕好句﹗這一聯對得工整﹗\n",
	}));
	// 文瀾茶肆供應清茶配的茶點吃食﹐沿用既有的糕餅乾糧物件。
	set("merchandise", ([
		"/obj/food/mooncake" : 30,
		"/obj/food/ricedough" : 40,
		"/obj/food/manto" : 50,
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
		return notify_fail("你想問茶博士些甚麼﹖（試試 ask teaman about 文國）\n");

	if( arg == "teaman about 文國"
	||  arg == "teaman about 文瀾"
	||  arg == "teaman about 茶肆"
	||  arg == "teaman about 文國縣"
	||  arg == "teaman about wenguo" ) {
		do_chat(({
			(: command, "say 客官是外鄉來的罷﹖咱這文國縣人稱『翰墨之鄉』﹐讀書人多﹐這文瀾茶肆便是縣中文士品茗論文、鬥詩聯句的去處﹐牆上的詩箋﹐都是茶客留下的。" :),
			(: command, "say 客官得了空﹐大街西北是制筆作坊﹐往北翰墨廣場東邊是松煙墨坊﹐都是看好筆好墨怎麼來的去處﹔廣場西邊那墨池小園﹐更是清幽﹐值得一遊。" :),
		}));
		return 1;
	}

	return notify_fail("茶博士正替客人續水﹐衝你溫文一笑﹕客官且坐下吃盞茶罷。\n");
}

int accept_fight(object ob)
{
	do_chat("茶博士忙不迭地擱下銅壺賠笑﹕客官息怒﹐有話坐下慢慢說﹐莫驚了滿堂的茶客。\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
