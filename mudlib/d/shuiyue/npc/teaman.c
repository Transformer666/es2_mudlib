// teaman.c -- 映月茶寮的茶博士（F_VENDOR 供應茶點吃食﹐純買賣 + 本地閒談）。
//             不接任務、不交物、不動任何旗標。

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

int do_ask(string arg);

void create()
{
	set_name("茶博士", ({ "teaman", "tea master", "shuiyue_teaman" }) );
	set("nickname", "茶博士");
	set_race("human");
	set_class("commoner");
	set_level(4);

	set("age", 36);
	set("gender", "male");
	set("long",
		"映月茶寮的茶博士生得清瘦斯文﹐一身青布長衫漿洗得乾乾\n"
		"淨淨﹐提著一把長嘴銅壺﹐遠遠地便能把滾水準準地續進客人的\n"
		"茶盞裡。他煮的茶用的是村後瀑下的活水﹐茶湯格外清甘﹐又愛\n"
		"與茶客閒談谷裡谷外的見聞。你可以用 list 看茶寮供應些什麼茶\n"
		"點﹐用 buy 向他點來嚐嚐。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"茶博士提著長嘴銅壺﹐手腕一抖﹐一道滾水準準地落進茶盞﹐滴水不濺。\n",
		"茶博士笑吟吟地道﹕客官嚐嚐這活水煮的清茶﹐配上一碟桂花糕﹐最是消閒。\n",
		"茶博士憑著竹欄望了望閣下的溪水道﹕咱這映月茶寮﹐圖的就是個臨水的清靜。\n",
	}));
	// 映月茶寮供應清茶配的茶點吃食﹐沿用既有的糕餅乾糧物件。
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
		return notify_fail("你想問茶博士些甚麼﹖（試試 ask teaman about 水月村）\n");

	if( arg == "teaman about 水月村"
	||  arg == "teaman about 映月"
	||  arg == "teaman about 茶寮"
	||  arg == "teaman about 水月"
	||  arg == "teaman about shuiyue" ) {
		do_chat(({
			(: command, "say 客官嚐得出罷﹖咱這茶用的是村後水月瀑布瀑下的活水﹐比尋常井水清甘十分﹐配什麼茶都出味。" :),
			(: command, "say 客官得了空﹐村心東北上去就是水月瀑布﹐月夜飛瀑映月﹐是難得一見的好景﹔東南柳堤下還有一泓浣月潭﹐都值得一遊。" :),
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
