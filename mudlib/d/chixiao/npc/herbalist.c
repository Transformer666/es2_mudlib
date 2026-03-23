// NPC: /d/chixiao/npc/herbalist.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("老藥農", ({"herbalist", "old herbalist"}));
	set_attr("str", 10);
	set_attr("dex", 12);
	set_attr("con", 14);
	set_attr("int", 16);
	set_attr("spi", 14);
	set_race("human");
	set_class("commoner");
	set_level(10);

	set("age", 55);
	set("gender", "male");
	set("long",
		"一個佝僂著腰的老藥農﹐皮膚黝黑粗糙﹐雙手沾滿了泥土和草\n"
		"汁。他的眼神卻十分清明﹐對各種藥草的性味瞭若指掌。他是村裡\n"
		"少數還願意在這片荒廢的藥圃裡勞作的人。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"老藥農嘆了口氣﹕這些藥草越來越難種了﹐地氣都不對了。\n",
		"老藥農自言自語道﹕當歸、黃芪、金銀花 ... 就剩這幾樣了。\n",
		"老藥農抬頭看了看天色﹐搖了搖頭。\n",
	}));
	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
}
