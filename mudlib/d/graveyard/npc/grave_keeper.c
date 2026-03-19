// grave_keeper.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("守墓人", ({"grave_keeper", "keeper"}));
	set_attr("str", 14);
	set_attr("con", 16);
	set_attr("dex", 12);
	set_race("human");
	set_class("commoner");
	set_level(12);

	set("age", 60);
	set("long",
		"一個形容枯槁的老人﹐穿著一件黑色的舊棉襖﹐臉色蠟黃﹐兩\n"
		"眼深陷。他獨自住在這破廟裡看守亂葬崗﹐也不知過了多少年。見\n"
		"到有人來﹐他也不驚不怕﹐只是淡淡地看了一眼。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"守墓人沙啞地說道﹕活人不該來這種地方﹐趕緊走吧。\n",
		"守墓人往火堆裡添了根柴﹐火光映照著他枯瘦的臉龐。\n",
		"守墓人嘆道﹕這裡埋著的都是些無名之輩﹐死了連個收屍的人都沒有。\n",
		"守墓人低聲說道﹕夜裡別出去﹐外面有些……不乾淨的東西。\n",
	}));
	setup();
	carry_money("coin", 25);
}
