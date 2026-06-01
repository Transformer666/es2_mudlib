// keeper.c -- 天仁客棧的掌櫃

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
		"這位是天仁客棧的掌櫃﹐生得清瘦﹐留著三綹山羊鬍﹐待人\n"
		"接物透著山城人家的厚道實在。倦了的話﹐不妨在這乾淨清靜\n"
		"的客棧裡尋張床鋪﹐好生歇歇腳。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"掌櫃撥著算盤﹐口中念念有詞地核著今日的帳目。\n",
		"掌櫃笑容可掬地招呼道﹕客官打尖還是住店﹖樓上的客房乾爽清靜﹐枕著山風睡個好覺哩﹗\n",
		"掌櫃捋著鬍子道﹕客官是打北邊喬陰縣翻山過來的罷﹖那盤山路可不好走哪﹐難為您了。\n",
	}));
	setup();
	carry_money("coin", 200);
}

void init()
{
	::init();
	if( !is_fighting() )
		do_chat((: command, "say 客官裡邊請﹗本店雖小﹐茶飯床鋪倒還齊整﹗" :));
}

int accept_fight(object player)
{
	do_chat("掌櫃陪笑道﹕這位客官說笑了﹐小老兒一介生意人﹐怎敢與您動手。\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
