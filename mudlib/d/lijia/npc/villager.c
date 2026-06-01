// villager.c -- 李家村心曬場上翻曬新穀的李家村婦（純氣氛閒談、隨意走動）。
//               不接任務、不交物、不動旗標。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("李家村婦", ({ "villager", "farm wife", "lijiacunfu" }) );
	set("nickname", "李家村婦");
	set_race("human");
	set_class("commoner");
	set_level(2);

	set("age", 38);
	set("gender", "female");
	set("long",
		"一個翻曬新穀的本村婦人﹐挽著袖子﹐圍著件半舊的藍布圍\n"
		"裙﹐裙角還沾著金黃的穀糠。她拿一柄木耙在曬場上來回翻穀﹐臉\n"
		"膛教日頭曬得紅撲撲的﹐透著莊稼人家的爽利勤快。論起來她也是\n"
		"李家的媳婦﹐村裡誰家的喜事、合族的祭祖﹐她倒是知道得最多。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		(: random_move :),
		"李家村婦拿木耙把曬場上的新穀來回翻勻﹐讓那金黃的穀子都曬著日頭。\n",
		"李家村婦直起腰捶了捶背﹐抹了把汗﹐瞇眼瞧瞧日頭﹐盤算著這場穀子曬透了好趁早入倉。\n",
		"李家村婦壓低嗓子和旁人道﹕聽說合族近日要在祠堂祭祖了﹐族長正張羅著備供品哩。\n",
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
		return notify_fail("你想跟這村婦打聽甚麼﹖（試試 ask villager about 李家村）\n");

	if( arg == "villager about 李家村"
	||  arg == "villager about 李家"
	||  arg == "villager about 曬場"
	||  arg == "villager about 村"
	||  arg == "villager about 祭祖"
	||  arg == "villager about lijia" ) {
		do_chat(({
			(: command, "say 客官是頭一回到咱李家村罷﹖咱這小村在雪亭鎮南邊﹐合村十之八九都姓李﹐論起來都是一個老祖宗的子孫﹐靠著村外的水田果園過活﹐日子過得安生平淡。" :),
			(: command, "say 近日合族要在西南頭的李氏祠堂祭祀先祖呢﹗族長正張羅著備三牲鮮果的供品。客官若得閒﹐去祠堂問問族長（ask elder about 祭祖），搭把手﹐也是一樁善緣。" :),
		}));
		return 1;
	}

	return notify_fail("李家村婦拿耙翻著穀子﹐憨憨一笑﹕客官問這做甚﹖閒著也是閒著﹐瞧咱這場好穀子罷。\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎哎哎﹗有話好說﹗光天化日曬穀的地界﹐動甚麼粗﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
