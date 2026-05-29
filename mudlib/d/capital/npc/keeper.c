// keeper.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("掌櫃", ({ "keeper", "innkeeper" }) );
	set_race("human");
	set_class("commoner");
	set_level(6);

	set("age", 55);
	set("gender", "male");
	set("long",
		"小樓客店的掌櫃﹐生得白胖富態﹐一身綢緞﹐一團和氣。他在這\n"
		"帝都的客店裡迎送了半輩子的達官貴客﹐眼力勁兒極好﹐見客人\n"
		"進門便堆起一臉的笑。倦了的話﹐不妨在客店裡好生歇歇。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"掌櫃撥著算盤﹐口中念念有詞地核著今日的帳目。\n",
		"掌櫃滿面春風地招呼道﹕客官打尖還是住店﹖小店的上房最是清靜雅致。\n",
		"掌櫃壓低聲音道﹕出了南城門往西﹐順著官道便是喬陰縣城﹐客官若要趕路﹐趁早動身的好。\n",
	}));
	setup();
	carry_money("coin", 500);
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
