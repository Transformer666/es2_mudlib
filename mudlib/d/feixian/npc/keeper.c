// keeper.c -- 悅客來客棧的掌櫃

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("掌櫃", ({ "keeper", "innkeeper", "feixian_keeper" }) );
	set("nickname", "掌櫃");
	set_race("human");
	set_class("commoner");
	set_level(5);

	set("age", 47);
	set("gender", "male");
	set("long",
		"這位是悅客來客棧的掌櫃﹐生得白胖和氣﹐一張笑臉終日不\n"
		"離﹐待客最是周到熱絡﹐難怪這「悅客來」三字的招牌叫得響。\n"
		"倦了的話﹐不妨在這乾淨清靜的客棧裡尋張床鋪﹐好生歇歇腳。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"掌櫃撥著算盤﹐口中念念有詞地核著今日的帳目。\n",
		"掌櫃笑容可掬地招呼道﹕客官打尖還是住店﹖樓上的客房乾爽清靜﹐保管睡個好覺﹗\n",
		"掌櫃捋著袖子道﹕客官是打喬陰那頭過來的罷﹖那條土道近來平整﹐走著倒也不累。\n",
	}));
	setup();
	carry_money("coin", 200);
}

void init()
{
	::init();
	if( !is_fighting() )
		do_chat((: command, "say 客官裡邊請﹗本店床鋪潔淨、茶飯齊整﹐包您住得稱心﹗" :));
}

int accept_fight(object player)
{
	do_chat("掌櫃陪笑道﹕這位客官說笑了﹐小老兒一介生意人﹐怎敢與您動手。\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
