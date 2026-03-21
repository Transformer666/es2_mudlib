// NPC: /d/lee/npc/temple_keeper.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("老廟祝", ({"temple_keeper", "keeper"}));
	set_race("human");
	set_class("commoner");
	set_level(5);

	set("age", 62);
	set("gender", "male");
	set("long",
		"一個瘦小的老人﹐穿著一件打了幾個補丁的灰布短衫﹐頭上包\n"
		"著一塊藍布巾。他是村裡土地廟的廟祝﹐每天早晚按時上香﹐把\n"
		"小廟打理得乾乾淨淨。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"老廟祝雙手合十﹐唸道﹕土地公保佑咱村風調雨順。\n",
		"老廟祝拿起撢子撣了撣供桌上的灰。\n",
		"老廟祝在香爐裡插上一炷香﹐青煙嫋嫋升起。\n",
	}));

	setup();
	carry_money("coin", 8);
}
