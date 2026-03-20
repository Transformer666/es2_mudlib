// NPC: /d/baihua/npc/innkeeper.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("客棧老闆娘", ({"innkeeper", "boss"}));
	set_race("human");
	set_class("commoner");
	set_level(8);

	set("age", 35);
	set("gender", "female");
	set("long",
		"一個和藹可親的中年婦人﹐頭上插著一朵鮮花﹐臉上帶著溫暖\n"
		"的笑容。她手腳麻利地打理著客棧的大小事務﹐把客棧佈置得像個\n"
		"小花園一樣溫馨。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"老闆娘笑道﹕客倌﹐喝杯花茶吧﹐是自家種的花曬的。\n",
		"老闆娘一邊擦桌子一邊說﹕咱們百花村﹐最不缺的就是花。\n",
		"老闆娘往花瓶裡插了一朵新摘的花。\n",
	}));

	setup();
	carry_money("coin", 50);
}

int accept_fight(object ob)
{
	do_chat("老闆娘嚇得連連擺手﹕哎呀﹐客倌別動手﹐有話好好說﹗\n");
	return 0;
}
