// hunter.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("獵人", ({"hunter", "huntsman"}));
	set_attr("str", 18);
	set_attr("con", 16);
	set_attr("dex", 20);
	set_race("human");
	set_class("commoner");
	set_level(15);

	set("age", 35);
	set("long",
		"一個身穿獸皮背心的獵人﹐皮膚被風吹日曬得黝黑粗糙。他腰\n"
		"間掛著一把獵刀﹐背上背著一張弓﹐目光銳利﹐時刻保持著警惕。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"獵人壓低聲音說道﹕別大聲﹐林子深處有黑熊出沒﹐惹不起。\n",
		"獵人看了看天色﹐說道﹕天黑前得趕回去﹐這林子夜裡更危險。\n",
		"獵人檢查了一下獵刀的鋒利程度﹐滿意地點了點頭。\n",
	}));
	setup();
	carry_object( STOCK_WEAPON("knife") )->wield();
	carry_money("coin", 60);
}
