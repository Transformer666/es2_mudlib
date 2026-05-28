// teaboy.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("茶博士", ({ "teaboy", "boy" }));
	set_race("human");
	set_level(3);

	set("gender", "male");
	set("long",
		"一個精瘦的中年茶博士﹐肩上搭著一條油亮的抹布﹐手腳俐落地在\n"
		"茶寮裡張羅著﹐見人進來總是笑臉相迎﹐熱絡地招呼著。\n");
	setup();
	carry_object("/obj/area/obj/cloth")->wear();
}

void init()
{
	::init();
	if( this_player() && interactive(this_player()) )
		do_chat((: command, "say 客官裡邊請﹐喝杯熱茶歇歇腳吧﹗" :));
}

// vim: set ts=4 sw=4 syntax=lpc
