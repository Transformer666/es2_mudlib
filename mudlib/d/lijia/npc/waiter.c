// waiter.c -- 李家小棧的店小二（純氣氛閒談、招呼住店）。
//             不接任務、不交物、不動旗標。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("店小二", ({ "waiter", "lijia waiter", "dianxiaoer" }) );
	set("nickname", "店小二");
	set_race("human");
	set_class("commoner");
	set_level(3);

	set("age", 22);
	set("gender", "male");
	set("long",
		"一個李家小棧的店小二﹐是李家一房的後生﹐生得眉眼伶俐﹐\n"
		"肩上搭著條洗得發白的抹布﹐成日價在堂屋裡張羅茶飯、招呼往來\n"
		"的客人﹐手腳麻利﹐一張嘴也甜。客官打尖住店、要碗熱飯﹐只管\n"
		"吩咐他便是。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"店小二拿抹布把桌面揩得乾乾淨淨﹐又給客人的粗茶碗續上了水。\n",
		"店小二笑容可掬地招呼道﹕客官裡邊請﹗本棧通鋪潔淨﹐灶上新米蒸的飯熱乎著哩﹗\n",
		"店小二一面理著櫃上的竹牌﹐一面哼著支不成調的鄉間小曲。\n",
	}));
	setup();
	carry_money("coin", 30);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這店小二甚麼﹖（試試 ask waiter about 李家村）\n");

	if( arg == "waiter about 李家村"
	||  arg == "waiter about 李家"
	||  arg == "waiter about 小棧"
	||  arg == "waiter about 客棧"
	||  arg == "waiter about 村"
	||  arg == "waiter about lijia" ) {
		do_chat(({
			(: command, "say 客官是打外鄉來的罷﹖咱李家小棧雖小﹐通鋪潔淨﹐灶上新米蒸的飯熱乎乎、香噴噴﹐包您住得稱心。要打尖住店﹐只管吩咐小的。" :),
			(: command, "say 咱這村合村都姓李﹐是個聚族而居的莊稼村子。村心西南是李氏祠堂﹐南面是果園﹐東南順田埂去是村南的魚塘。客官得空都去逛逛﹐村裡人都和氣著哩。" :),
		}));
		return 1;
	}

	return notify_fail("店小二陪笑道﹕客官若是打尖住店、吃碗熱飯﹐只管吩咐小的﹐旁的小的可說不上來。\n");
}

int accept_fight(object ob)
{
	do_chat("店小二連忙縮手陪笑﹕客官有話好說﹗小的一個跑堂的後生﹐怎敢與您動手﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
