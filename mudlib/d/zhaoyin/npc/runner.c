// runner.c -- 兆隱縣衙前當值的老捕快（純氣氛 NPC）

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("捕快", ({ "runner", "constable", "bushou" }) );
	set_race("human");
	set_class("commoner");
	set_level(6);

	set("age", 41);
	set("gender", "male");
	set("long",
		"一名兆隱縣衙的捕快﹐穿著件半舊的青色號褂﹐腰間斜插一\n"
		"根烏木水火棍。他這差事在這太平小縣清閒得很﹐一年到頭也\n"
		"拿不著幾個賊﹐成日價背著手在衙門前踱來踱去﹐連腰桿都站\n"
		"得鬆鬆垮垮的。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		(: random_move :),
		"捕快打了個長長的呵欠﹐伸著懶腰嘟囔﹕這日子﹐閒得骨頭都要鏽了。\n",
		"捕快按著腰刀慢悠悠地踱步﹐沒精打采地掃視著街面。\n",
		"捕快瞇眼瞧了瞧你﹐懶懶地道﹕生面孔啊﹖在咱兆隱縣﹐安分守己便好﹐莫要惹事。\n",
	}));
	setup();
	carry_money("coin", 30);
}

int accept_fight(object ob)
{
	do_chat("捕快這才來了精神﹐抽出水火棍喝道﹕反了你了﹗光天化日竟敢在縣衙門前撒野﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
