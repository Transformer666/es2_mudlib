// scholar.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("書生", ({ "scholar", "shusheng" }) );
	set_race("human");
	set_class("scholar");
	set_level(6);

	set("age", 24);
	set("gender", "male");
	set("long",
		"一個年輕的書生﹐頭戴儒巾﹐身著青布直裰﹐手裡搖著一柄折\n"
		"扇﹐眉宇間透著幾分清高﹐想是進城來趕考或訪友的讀書人。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		"書生搖著折扇﹐負手望天﹐口中念念有詞地推敲著詩句。\n",
		"書生拱手道﹕兄台也是讀書人麼﹖城西的喬陰書局藏書頗豐﹐值得一逛。\n",
		"書生歎道﹕十年寒窗無人問﹐只盼著來年秋闈能搏個功名。\n",
		"書生說道﹕讀萬卷書﹐行萬里路﹐買本好書回去 study 細研﹐方是正經。\n",
	}));
	setup();
	carry_money("coin", 50);
}

int accept_fight(object ob)
{
	do_chat("書生臉色發白﹐連連後退道﹕君子動口不動手﹐你 ... 你莫要無禮﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
