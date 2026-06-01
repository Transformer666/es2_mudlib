// villager.c -- 康平村心曬場上翻曬新穀的村婦（純氣氛閒談、隨意走動）。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("曬穀村婦", ({ "villager", "farm wife", "shaigucunfu" }) );
	set("nickname", "曬穀村婦");
	set_race("human");
	set_class("commoner");
	set_level(2);

	set("age", 37);
	set("gender", "female");
	set("long",
		"一個翻曬新穀的本村婦人﹐挽著袖子﹐圍著件半舊的藍布圍\n"
		"裙﹐裙角還沾著金黃的穀糠。她拿一柄木耙在曬場上來回翻穀﹐臉\n"
		"膛教日頭曬得紅撲撲的﹐透著莊稼人家的爽利勤快﹐村裡誰家的喜\n"
		"事閒話﹐她倒是知道得最多。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		(: random_move :),
		"曬穀村婦拿木耙把曬場上的新穀來回翻勻﹐讓那金黃的穀子都曬著日頭。\n",
		"曬穀村婦直起腰捶了捶背﹐抹了把汗﹐瞇眼瞧瞧日頭﹐盤算著這場穀子曬透了好趁早入倉。\n",
		"曬穀村婦壓低嗓子和旁人道﹕聽說村裡要辦秋收謝場了﹐小店店家正張羅著蒸新米飯糰哩。\n",
	}));
	setup();
	carry_money("coin", 10);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想跟這村婦打聽甚麼﹖（試試 ask villager about 康平村）\n");

	if( arg == "villager about 康平村"
	||  arg == "villager about 康平"
	||  arg == "villager about 曬場"
	||  arg == "villager about 村"
	||  arg == "villager about 新米"
	||  arg == "villager about 謝場"
	||  arg == "villager about kangping" ) {
		do_chat(({
			(: command, "say 客官瞧這滿場的新穀﹗今年年成好﹐家家戶戶都收得豐足﹐曬乾了入倉﹐這一冬可不愁嚼裹嘍。咱莊稼人﹐圖的就是這秋收進倉的踏實。" :),
			(: command, "say 聽說村裡要在這曬場上辦一場秋收謝天的酒飯哩﹗康平小店的店家正張羅著蒸頭一籠待客的新米飯糰呢。客官若得閒﹐去小店問問店家（ask keeper about 新米），搭把手﹐也熱鬧熱鬧。" :),
		}));
		return 1;
	}

	return notify_fail("曬穀村婦拿耙翻著穀子﹐憨憨一笑﹕客官問這做甚﹖閒著也是閒著﹐瞧咱這場好穀子罷。\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎哎哎﹗有話好說﹗光天化日曬穀的地界﹐動甚麼粗﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
