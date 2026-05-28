// keeper.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("掌櫃", ({ "keeper", "innkeeper" }) );
	set_race("human");
	set_class("commoner");
	set_level(5);

	set("age", 52);
	set("gender", "male");
	set("long",
		"這位是悅來客棧的掌櫃﹐生得白胖富態﹐一團和氣﹐手裡的算\n"
		"盤撥得出神入化﹐見客人進門便堆起一臉的笑。倦了的話﹐不妨\n"
		"在客棧裡好生歇歇。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"掌櫃撥著算盤﹐口中念念有詞地核著今日的帳目。\n",
		"掌櫃滿面春風地招呼道﹕客官打尖還是住店﹖樓上的雅間最是清靜。\n",
		"掌櫃壓低聲音道﹕往西北過了老松林便是雪亭鎮﹐只是近來老松寨的匪人猖獗﹐客官夜裡可別趕路。\n",
	}));
	setup();
	carry_money("coin", 300);
}

void init()
{
	::init();
	if( !is_fighting() )
		do_chat((: command, "say 客官裡邊請﹗本店上房雅座一應俱全﹗" :));
}

int accept_fight(object player)
{
	do_chat("掌櫃陪笑道﹕這位客官說笑了﹐小老兒一介生意人﹐怎敢與您動手。\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
