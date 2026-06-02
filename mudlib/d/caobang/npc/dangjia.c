// dangjia.c -- 漕幫酒館的船家掌櫃（F_VENDOR 販售既有的 /obj/food 吃食﹐純買賣 + 閒談）。
//              不接任務、不交物、不動任何旗標。沿用既有吃食物件﹐以英文 id 設 merchandise。

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

int do_ask(string arg);

void create()
{
	set_name("船家", ({ "boatman host", "dangjia", "host", "vendor" }) );
	set("nickname", "船家");
	set_race("human");
	set_class("commoner");
	set_level(6);

	set("age", 39);
	set("gender", "male");
	set("long",
		"櫃後一個精壯黝黑的船家﹐袖子捲得老高﹐露出一雙青筋虯結\n"
		"的手臂。他原也是漕幫跑船的﹐如今上了岸﹐守著這河邊的小酒\n"
		"館﹐既當掌櫃又當夥計﹐燙酒、上菜、收錢﹐一個人張羅得團團\n"
		"轉。他臉上常掛著做生意的和氣笑﹐和過往的船工最是熟絡。你可\n"
		"以用 list 看他賣些甚麼吃食﹐用 buy 向他買。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"船家在熱水鍋上燙著一壺渾酒﹐衝著進門的客人吆喝﹕來啦客官﹗熱酒熱菜﹐裡邊坐﹗\n",
		"船家麻利地抹了把油膩的桌面﹐又給熟客的碗裡續上酒﹐笑呵呵地插了句渾話。\n",
		"船家一面顛著炒勺﹐一面道﹕咱這小館子﹐養的全是漕幫跑船的弟兄﹐圖個熱鬧自在﹗\n",
	}));
	// 漕幫酒館﹐沿用既有的乾糧吃食物件販售（皆 /obj/food 既有物件﹐以英文 id 認貨）。
	set("merchandise", ([
		"/obj/food/manto" : 50,
		"/obj/food/pork" : 30,
		"/obj/food/dumpling" : 40,
		"/obj/food/ricedough" : 40,
		"/obj/food/fish" : 30,
		"/obj/food/mooncake" : 20,
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
		return notify_fail("你想問這船家些甚麼﹖（試試 ask host about 漕幫）\n");

	if( arg == "host about 漕幫"
	||  arg == "host about 酒館"
	||  arg == "host about 渡口"
	||  arg == "host about caobang"
	||  arg == "boatman host about 漕幫" ) {
		do_chat(({
			(: command, "say 客官頭一回逛咱這漕幫的渡口罷﹖坐坐坐﹗咱這小館子﹐酒是渾酒﹐菜是粗菜﹐圖的就是個實在熱鬧。跑船的弟兄卸完了貨﹐都愛擠到我這兒來灌兩碗、歇歇乏。" :),
			(: command, "say 客官要打聽幫裡的事﹐往北禮堂裡尋宋爺、江爺﹔要歇腳吃喝﹐我這兒管夠。咱漕幫和氣生財、四海皆朋友﹐從不跟人結梁子的——客官只管寬心吃喝﹗用 list 瞧瞧﹐想要甚麼只管 buy。" :),
		}));
		return 1;
	}

	return notify_fail("船家搓著手憨笑﹕客官要吃點甚麼﹖只管 list 來瞧﹐熱酒熱菜管夠﹗\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎哎哎﹗客官息怒﹗有話好好說﹗咱一個賣酒的本分人﹐這館子裡可動不得粗﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
