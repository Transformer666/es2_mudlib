// yaotong.c -- 百藥谷藥圃裡照管藥田的藥童（F_VILLAGER﹐純氣氛、非戰鬥）。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("藥童", ({ "yaotong", "herb boy", "boy" }) );
	set("nickname", "藥童");
	set_race("human");
	set_class("commoner");
	set_level(3);

	set("age", 13);
	set("gender", "male");
	set("long",
		"一個十二三歲的藥童﹐生得眉清目秀﹐挽著褲腳赤著腳﹐手裡\n"
		"提著個半滿的竹籃。他成日在藥圃裡跟著大人采藥、晾藥、引水\n"
		"灌溉﹐曬得黝黑卻透著一股機靈勁兒。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"藥童蹲在田壟間﹐小心翼翼地撥開朽木看那叢靈芝﹐口中念念有詞地數著日子。\n",
		"藥童提著竹籃跑來跑去﹐脆生生地道﹕這畦當歸還沒長足﹐師公說再等半月才好採哩。\n",
		"藥童拿小耙子在田裡鬆土﹐一面哼著不成調的採藥歌。\n",
	}));

	setup();
}

int accept_fight(object ob)
{
	do_chat("藥童嚇得抱起竹籃就往師公那兒躲﹕你 ... 你別過來呀﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
