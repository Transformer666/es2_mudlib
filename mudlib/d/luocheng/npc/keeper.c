// keeper.c -- 羅城客棧的掌櫃

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("掌櫃", ({ "luocheng keeper", "keeper", "innkeeper" }) );
	set_race("human");
	set_class("commoner");
	set_level(5);

	set("age", 50);
	set("gender", "male");
	set("long",
		"這位是羅城客棧的掌櫃﹐生得圓臉福相﹐一雙眼睛笑成了兩\n"
		"道縫﹐一手算盤撥得劈啪作響﹐一張嘴更是八面玲瓏。他迎送\n"
		"的多是候缺謁選的官人﹐應對進退極有分寸﹐連奉承都奉承得\n"
		"不著痕跡。倦了的話﹐不妨在這客棧裡好生歇歇。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"掌櫃撥著算盤﹐口中念念有詞地核著今日的帳目。\n",
		"掌櫃滿面堆笑地招呼道﹕這位老爺打尖還是住店﹖樓上的上房清靜雅致﹐最宜養神哩﹗\n",
		"掌櫃壓低聲音道﹕往西出城走上一程便是帝都京畿了﹐老爺是要進京謁選的罷﹖小店住的多是這樣的貴客哩。\n",
	}));
	setup();
	carry_money("coin", 300);
}

int accept_fight(object player)
{
	do_chat("掌櫃陪笑道﹕這位老爺說笑了﹐小老兒一介生意人﹐怎敢與您動手。\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
