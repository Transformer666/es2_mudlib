// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("黑衣老人", ({"heiyilaoren", "old man", "oldman"}));
	set_attr("str", 20);
	set_attr("dex", 22);
	set_attr("con", 18);
	set_attr("int", 24);
	set_attr("spi", 26);
	set_attr("wis", 25);
	set_race("human");
	set_class("commoner");
	set_level(40);

	set_skill("sword", 80);
	set_skill("dodge", 70);
	set_skill("parry", 65);
	set_skill("force", 75);

	set("age", 70);
	set("gender", "male");
	set("long",
		"一個身穿黑色長袍的老人﹐面容枯瘦﹐雙目卻炯炯有神﹐透著\n"
		"一股看穿世事的滄桑。他靜靜地坐在角落裡﹐似乎在等待著什麼。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"黑衣老人喃喃自語：時候到了嗎 ... 還沒有 ...\n",
		"黑衣老人靜靜地望著遠方﹐陷入沉思。\n",
		"黑衣老人輕嘆一聲﹐搖了搖頭。\n",
	}));
	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
	carry_object(STOCK_WEAPON("longsword"))->wield();
	carry_money("coin", 100);
}
