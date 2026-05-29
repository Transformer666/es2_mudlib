// keeper.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("掌櫃", ({ "keeper", "innkeeper" }) );
	set_race("human");
	set_class("commoner");
	set_level(5);

	set("age", 49);
	set("gender", "male");
	set("long",
		"這位是春風客棧的掌櫃﹐生得膀大腰圓﹐一張被朔風颳得通\n"
		"紅的臉上堆滿了笑﹐手裡的算盤撥得劈啪作響。倦了的話﹐不\n"
		"妨在客棧裡圍著炭火好生歇歇。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"掌櫃撥著算盤﹐口中念念有詞地核著今日的帳目。\n",
		"掌櫃滿面春風地招呼道﹕客官打尖還是住店﹖樓上盡是燒著火炕的暖房﹗\n",
		"掌櫃壓低聲音道﹕往南出城過了那片原野﹐一路便通帝都京畿﹐只是道兒遠﹐客官路上可得當心塞外的馬賊。\n",
	}));
	setup();
	carry_money("coin", 300);
}

void init()
{
	::init();
	if( !is_fighting() )
		do_chat((: command, "say 客官裡邊請﹗快來火邊暖暖身子﹗本店上房雅座一應俱全﹗" :));
}

int accept_fight(object player)
{
	do_chat("掌櫃陪笑道﹕這位客官說笑了﹐小老兒一介生意人﹐怎敢與您動手。\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
