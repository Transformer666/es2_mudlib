// keeper.c -- 望安客棧的掌櫃

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
		"這位是望安客棧的掌櫃﹐生得圓臉福相﹐一雙眼睛笑成了兩\n"
		"道縫﹐手裡的算盤撥得劈啪作響。倦了的話﹐不妨在這臨水的\n"
		"客棧裡推窗望海﹐好生歇歇。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"掌櫃撥著算盤﹐口中念念有詞地核著今日的帳目。\n",
		"掌櫃滿面笑容地招呼道﹕客官打尖還是住店﹖樓上的客房臨著港面﹐推窗便是滿港的漁火哩﹗\n",
		"掌櫃壓低聲音道﹕往東出城走上一程﹐便是北方大城風城了﹐客官是打那邊來的麼﹖\n",
	}));
	setup();
	carry_money("coin", 300);
}

void init()
{
	::init();
	if( !is_fighting() )
		do_chat((: command, "say 客官裡邊請﹗本店臨著望安港﹐上房雅座一應俱全﹗" :));
}

int accept_fight(object player)
{
	do_chat("掌櫃陪笑道﹕這位客官說笑了﹐小老兒一介生意人﹐怎敢與您動手。\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
