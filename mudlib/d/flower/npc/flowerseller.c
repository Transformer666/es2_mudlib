// flowerseller.c -- 百花村村口賣花的老嫗（純氣氛閒談 + 本地指路﹐不接任務、
// 不動旗標）。模式照 d/shuiyue/npc/porter.c：F_VILLAGER、do_ask 只擺風味與指路、
// accept_fight 回 0。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("賣花老嫗", ({ "flower seller", "flowerseller", "old woman", "laoyu" }) );
	set("nickname", "賣花老嫗");
	set_race("human");
	set_class("commoner");
	set_level(2);

	set("age", 63);
	set("gender", "female");
	set("long",
		"一個在村口賣花的老嫗﹐鬢髮已然花白﹐臉上的皺紋裡卻盛著\n"
		"一團和氣。她挎著只半舊的竹籃﹐籃裡盛著時新的桃花杏蕊﹑芍\n"
		"藥薔薇﹐見有人經過便笑吟吟地招呼﹐想兜售幾枝。她在這村口\n"
		"賣了大半輩子的花﹐百花村裡裡外外的門路掌故﹐沒有她不曉得\n"
		"的。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		(: random_move :),
		"賣花老嫗理了理籃中的鮮花﹐拈起一枝芍藥往鼻尖一湊﹐瞇眼笑了。\n",
		"賣花老嫗朝你招呼道﹕客官﹐買枝花戴罷﹖咱百花村的花﹐比那胭脂水粉還香三分哩。\n",
		"賣花老嫗望著街心那一片紅燈﹐喃喃道﹕這村裡的脂粉富貴﹐到頭來﹐還不如我這一籃鮮花活得自在。\n",
	}));
	setup();
	carry_money("coin", 15);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這賣花老嫗甚麼﹖（試試 ask flowerseller about 百花村）\n");

	if( arg == "flowerseller about 百花村"
	||  arg == "flowerseller about 村"
	||  arg == "flowerseller about flower"
	||  arg == "flower seller about 百花村"
	||  arg == "old woman about 百花村" ) {
		do_chat(({
			(: command, "say 客官順著這街往北走﹐便是村心了﹕當街那座燈火最盛的﹐是紅燈客棧﹔東邊一座繡樓﹑西邊一爿茶寮﹐打尖歇腳﹑聽曲吃茶﹐樣樣都便當。" :),
			(: command, "say 咱這百花村哪﹐春來桃杏滿坡﹑落英十里﹐村名便是這般得來的——只是這些年脂粉風月的買賣紅火﹐三教九流的都往這兒湊﹐倒把那一村的花香﹐都壓住了。" :),
		}));
		return 1;
	}

	if( arg == "flowerseller about 符"
	||  arg == "flowerseller about 公孫志"
	||  arg == "flowerseller about gongsunzhi"
	||  arg == "flowerseller about 道人" ) {
		do_chat((: command, "say 客官說那位青袍道長啊﹖他就寓在當街的紅燈客棧裡頭﹐成日就著燈火書他的符。聽說那符能驅邪護心哩﹐客官若與他投緣﹐不妨上前問問。" :));
		return 1;
	}

	return notify_fail("賣花老嫗呵呵一笑﹕客官問這個做甚﹖買枝花戴﹐進村逛逛去罷。\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎喲﹗客官這是做甚﹖咱一個賣花的老婆子﹐與你無冤無仇哪﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
