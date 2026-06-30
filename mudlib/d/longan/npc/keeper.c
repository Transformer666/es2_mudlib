// keeper.c -- 枕流居客棧的掌櫃（尋常villager﹐招呼住店）。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("掌櫃", ({ "keeper", "innkeeper", "longan_keeper" }) );
	set("nickname", "掌櫃");
	set_race("human");
	set_class("commoner");
	set_level(4);

	set("age", 52);
	set("gender", "male");
	set("long",
		"枕流居的掌櫃生得清瘦﹐留著三綹花白的鬍子﹐手裡的算盤撥得\n"
		"滴溜溜地響。他在這水鄉客棧裡待了大半輩子﹐閱人無數﹐見客人\n"
		"進來便堆起一臉的和氣招呼。累了的話﹐不妨在這枕流居裡枕著水\n"
		"聲好生歇上一宿。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"掌櫃撥著算盤﹐口中念念有詞地算著今日的房錢。\n",
		"掌櫃笑瞇瞇地招呼道﹕客官打尖還是住店﹖樓上的水閣客房﹐枕著流水睡﹐最是養神。\n",
		"掌櫃捋著鬍子說道﹕咱龍安別的不多﹐就水多、酒香多。客官得空﹐去街南無腸酒店嚐嚐咱的米酒罷。\n",
	}));
	setup();
	carry_money("coin", 200);
}

void init()
{
	::init();
	// 只對真人玩家招呼（gotcha #14：缺 interactive 護衛會被漫遊NPC觸發成say-storm）。
	if( this_player() && interactive(this_player()) && !is_fighting() )
		do_chat((: command, "say 客官裡邊請﹗枕流居的水閣客房﹐枕著溪聲睡﹐管教你一夜好夢﹗" :));
}

int accept_fight(object player)
{
	do_chat("掌櫃連連擺手陪笑﹕客官息怒﹗有話好說﹐小店這就給您換間清靜上房﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
