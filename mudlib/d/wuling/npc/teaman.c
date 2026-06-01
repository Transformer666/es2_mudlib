// teaman.c -- 醉月茶寮的茶博士（F_VENDOR 供應茶酒茶點﹐純氣氛閒談）。
//             水嵐武陵是冷梅莊所在的桃花源式小鎮﹐此處只作清雅閒談﹐
//             不接任何任務、不動任何旗標。

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

int do_ask(string arg);

void create()
{
	set_name("茶博士", ({ "teaman", "tea master", "wuling_teaman" }) );
	set("nickname", "茶博士");
	set_race("human");
	set_class("commoner");
	set_level(4);

	set("age", 42);
	set("gender", "male");
	set("long",
		"醉月茶寮的茶博士是個閒雲野鶴般的人物﹐一身洗得發白的\n"
		"葛布長衫﹐花白的鬢角梳得齊整﹐提著一把長嘴錫壺﹐替臨溪而\n"
		"坐的茶客續水添酒。他煮得一手好茶﹐又釀得一甕好桃花酒﹐閒\n"
		"來便愛對著溪上桃花﹐與茶客說些武陵的舊事閒話。你可以用\n"
		"list 看茶寮供應些什麼茶酒茶點﹐用 buy 向他點來嚐嚐。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"茶博士提著長嘴錫壺﹐手腕輕輕一抖﹐一道滾水準準地落進茶盞﹐滴水不濺。\n",
		"茶博士望著窗外溪上的落花﹐悠然道﹕在武陵吃茶﹐圖的就是這一份閒散。\n",
		"茶博士笑吟吟地道﹕客官嚐嚐這溪魚羹﹐配一塊桃花糕﹐再篩一壺桃花酒﹐神仙也不換哩。\n",
	}));
	// 茶寮供應溪鮮茶點與本地桃花糕﹐另沿用既有的糕餅饅頭物件。
	set("merchandise", ([
		"/d/wuling/obj/fishstew" : 1,
		"/d/wuling/obj/peachcake" : 1,
		"/obj/food/mooncake" : 30,
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
		return notify_fail("你想問茶博士些甚麼﹖（試試 ask teaman about 武陵）\n");

	if( arg == "teaman about 武陵"
	||  arg == "teaman about 水嵐"
	||  arg == "teaman about 醉月"
	||  arg == "teaman about 茶寮"
	||  arg == "teaman about wuling" ) {
		do_chat(({
			(: command, "say 客官是頭一回到水嵐武陵罷﹖咱這小鎮三面環山﹐一道水嵐溪繞鎮而過﹐溪畔遍植桃林﹐每逢三月落英繽紛﹐外鄉人來了﹐都道是誤入了桃花源哩。" :),
			(: command, "say 鎮上不爭不搶﹐連那渡口的船夫都慢悠悠的。客官得閒﹐就在咱這臨溪的茶座坐坐﹐看溪水﹐聽桃花﹐什麼煩心事都淡了。" :),
		}));
		return 1;
	}

	if( arg == "teaman about 桃花酒"
	||  arg == "teaman about 酒"
	||  arg == "teaman about wine" ) {
		do_chat(({
			(: command, "say 咱這桃花酒﹐是拿三月桃林裡頭一場的落花﹐連著山泉、糯米下甕﹐埋在溪邊柳樹下足足窖一年纔起的。揭甕那天﹐半條街都聞得見香。" :),
			(: command, "say 客官若不急著趕路﹐篩上一壺﹐就著溪上的桃花慢慢吃﹐保管醉得也風雅。" :),
		}));
		return 1;
	}

	return notify_fail("茶博士正替客人續水﹐衝你溫文一笑﹕客官且坐下吃盞茶罷。\n");
}

int accept_fight(object ob)
{
	do_chat("茶博士忙不迭地擱下錫壺賠笑﹕客官息怒﹐有話坐下慢慢說﹐莫驚了滿堂吃茶的客人。\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
