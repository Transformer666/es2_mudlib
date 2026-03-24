// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("採藥婆婆", ({"herbalist", "old woman", "herb woman"}));
	set_attr("str", 8);
	set_attr("con", 10);
	set_attr("dex", 12);
	set_attr("int", 18);
	set_attr("spi", 16);
	set_race("human");
	set_class("commoner");
	set_level(10);

	set("age", 65);
	set("gender", "female");
	set("long",
		"一位滿頭銀髮的老婦人﹐面色紅潤﹐精神矍鑠。她身旁放著\n"
		"一個大竹簍﹐裡面裝著各種新鮮的草藥。她是村裡唯一懂得\n"
		"醫術的人﹐鄉親們有個頭疼腦熱都來找她。你可以用 list\n"
		"看看她有什麼藥材﹐用 buy 來買。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"採藥婆婆仔細地查看著藥園裡的藥材﹐不時拔去幾棵雜草。\n",
		"採藥婆婆說道﹕這金銀花長得真好﹐今年又能曬不少。\n",
		"採藥婆婆說道﹕山裡的藥材越來越難找了﹐還好園子裡的夠用。\n",
	}));
	set("merchandise", ([
		__DIR__"obj/herb" : 50,
		__DIR__"obj/healing_herb" : 120,
		__DIR__"obj/antidote_herb" : 80,
	]));
	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
	carry_money("coin", 200);
}

int accept_fight(object ob)
{
	do_chat("採藥婆婆驚道﹕哎呀﹐大俠你可別嚇老婆子啊﹗\n");
	return 0;
}
