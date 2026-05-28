// keeper.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("掌櫃", ({ "keeper", "innkeeper" }) );
	set_race("human");
	set_class("commoner");
	set_level(4);

	set("age", 49);
	set("gender", "male");
	set("long",
		"這位是飲鶴居的掌櫃﹐生得圓臉細眼﹐一團和氣﹐手裡的算盤撥得\n"
		"飛快﹐見客人進來便笑著招呼。累了的話﹐不妨在客棧裡歇歇腳。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"掌櫃撥著算盤﹐口中念念有詞地算著今日的帳。\n",
		"掌櫃招呼道﹕客官打尖還是住店﹖樓上雅淨的客房盡有。\n",
		"掌櫃壓低了聲音說道﹕近來松林裡不太平﹐夜裡趕路可得小心些。\n",
	}));
	setup();
	carry_money("coin", 200);
}

void init()
{
	::init();
	if( !is_fighting() )
		do_chat((: command, "say 客官裡邊請﹗打尖住店都使得﹗" :));
}

int accept_fight(object player)
{
	do_chat("掌櫃陪笑道﹕這位客官說笑了﹐小老兒還指著這客棧過活呢。\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
