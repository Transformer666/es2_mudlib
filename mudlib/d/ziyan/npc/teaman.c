// teaman.c -- 煮泉茶寮的茶博士（F_VENDOR 兼賣佐茶的茶食點心與趕路乾糧﹐
//             純氣氛閒談）。紫煙鎮是倚溫泉而築的小鎮﹐此處只作清雅閒談﹐
//             不接任何任務、不動任何旗標。

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

int do_ask(string arg);

void create()
{
	set_name("茶博士", ({ "teaman", "tea master", "ziyan_teaman" }) );
	set("nickname", "茶博士");
	set_race("human");
	set_class("commoner");
	set_level(4);

	set("age", 41);
	set("gender", "male");
	set("long",
		"煮泉茶寮的茶博士是個健談爽朗的本鎮人﹐一身被湯氣與茶\n"
		"煙養得鬆軟的葛布長衫﹐提著一把長嘴銅壺﹐替泡完溫泉來歇腳\n"
		"的茶客續水添茶。他取鎮南溫泉新汲的活水煮茶﹐又愛在軒角煨\n"
		"一爐沉香﹐閒來便對著裊裊的紫煙﹐與茶客說些鎮裡的閒話。你\n"
		"可以用 list 看茶寮供應些什麼茶食﹐用 buy 向他點來嚐嚐。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"茶博士提著長嘴銅壺﹐手腕輕輕一抖﹐一道滾水準準地落進茶盞﹐滴水不濺。\n",
		"茶博士望著軒外裊裊的紫煙﹐悠然道﹕在紫煙鎮吃茶﹐圖的就是這一份溫煦閒散。\n",
		"茶博士笑吟吟地道﹕客官泡完溫泉﹐就著這溫泉煮的茶、煨的沉香歇歇﹐渾身的乏都化開了哩。\n",
	}));
	// 茶寮兼賣佐茶的茶食點心與趕路乾糧﹐沿用既有的糕餅乾糧物件販售。
	set("merchandise", ([
		"/obj/food/mooncake" : 30,
		"/obj/food/manto" : 50,
		"/obj/food/ricedough" : 45,
		"/obj/food/dumpling" : 60,
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
		return notify_fail("你想問茶博士些甚麼﹖（試試 ask teaman about 紫煙鎮）\n");

	if( arg == "teaman about 紫煙鎮"
	||  arg == "teaman about 紫煙"
	||  arg == "teaman about 煮泉"
	||  arg == "teaman about 茶寮"
	||  arg == "teaman about ziyan" ) {
		do_chat(({
			(: command, "say 客官是頭一回到紫煙鎮罷﹖咱這小鎮倚著一眼天然的溫泉過活﹐湯氣裊裊﹐晨昏斜照一映便泛出淡淡的紫煙﹐外鄉人來了﹐都道是入了甚麼仙境哩。" :),
			(: command, "say 鎮上不爭不搶﹐圖個溫煦自在。客官得閒﹐先去鎮南泡個溫泉﹐再回我這茶寮﹐就著溫泉煮的茶、煨的沉香坐坐﹐什麼煩心事都淡了。" :),
		}));
		return 1;
	}

	if( arg == "teaman about 溫泉"
	||  arg == "teaman about 沉香"
	||  arg == "teaman about 茶"
	||  arg == "teaman about tea" ) {
		do_chat(({
			(: command, "say 咱這茶﹐取的全是鎮南紫煙溫泉新汲的活水煮的。那泉水含著地底的礦氣﹐煮出的茶湯回甘綿軟﹐比尋常井水強上幾分﹐客官嚐嚐便知。" :),
			(: command, "say 軒角那爐沉香﹐是鎮上焙香人焙的﹐借溫泉湯氣慢養﹐香味綿長安神。一壺溫泉茶﹐一爐好沉香﹐再就著裊裊的紫煙﹐神仙也不換哩。" :),
		}));
		return 1;
	}

	return notify_fail("茶博士正替客人續水﹐衝你溫文一笑﹕客官且坐下吃盞茶罷。\n");
}

int accept_fight(object ob)
{
	do_chat("茶博士忙不迭地擱下銅壺賠笑﹕客官息怒﹐有話坐下慢慢說﹐莫驚了滿堂吃茶的客人。\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
