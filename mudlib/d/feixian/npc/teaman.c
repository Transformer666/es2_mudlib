// teaman.c -- 清風茶行的茶博士（F_VENDOR 供應茶點吃食）

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

int do_ask(string arg);

void create()
{
	set_name("茶博士", ({ "teaman", "tea master", "feixian_teaman" }) );
	set("nickname", "茶博士");
	set_race("human");
	set_class("commoner");
	set_level(4);

	set("age", 38);
	set("gender", "male");
	set("long",
		"店裡的茶博士生得清瘦斯文﹐一身青布長衫漿洗得乾乾淨\n"
		"淨﹐提著一把長嘴銅壺﹐遠遠地便能把滾水準準地續進客人的茶\n"
		"盞裡﹐手法俐落漂亮。他煮得一手好茶﹐又愛與茶客閒談古今。\n"
		"你可以用 list 看茶行供應些什麼茶點﹐用 buy 向他點來嚐嚐。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"茶博士提著長嘴銅壺﹐手腕一抖﹐一道滾水準準地落進茶盞﹐滴水不濺。\n",
		"茶博士笑吟吟地道﹕客官嚐嚐這雨前的新茶﹐配上一碟桂花糕﹐最是消閒。\n",
		"茶博士搖著扇子道﹕咱這清風茶行﹐圖的就是個清靜﹐外頭路口再鬧﹐進得門來便聽不見了。\n",
	}));
	// 茶行供應清茶配的茶點吃食﹐沿用既有的糕餅乾糧物件。
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
		return notify_fail("你想問茶博士些甚麼﹖（試試 ask teaman about 斐縣）\n");

	if( arg == "teaman about 斐縣"
	||  arg == "teaman about 清風"
	||  arg == "teaman about 茶行"
	||  arg == "teaman about feixian" ) {
		do_chat(({
			(: command, "say 斐縣雖小﹐倒是個有來歷的去處。城中那五向路口﹐五條道通著五處地界﹐打喬陰來的、進山去的﹐都得打這兒過﹐斐縣這名號﹐便是這般傳開的。" :),
			(: command, "say 客官若往南邊山裡走﹐途中有座武陀灸堂﹐裡頭的針灸艾灸是出了名的妙手回春﹐進山前不妨先去討個平安。" :),
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
