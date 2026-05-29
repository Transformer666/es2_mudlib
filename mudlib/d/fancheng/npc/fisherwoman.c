// fisherwoman.c -- 檒城大街上叫賣鮮魚的漁婦（純氣氛 NPC）

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("漁婦", ({ "fisherwoman", "woman", "fisher woman" }) );
	set_race("human");
	set_class("commoner");
	set_level(2);

	set("age", 39);
	set("gender", "female");
	set("long",
		"一個爽利的討海人家婦人﹐挽著褲腳﹐赤著一雙沾滿泥沙的\n"
		"腳﹐挑著一擔剛上岸的鮮魚。她臉膛被海風與日頭曬得通紅﹐\n"
		"嗓門卻響亮得很﹐一張口便是滿滿的海腥氣與市井的潑辣勁。\n");
	set("chat_chance", 5);
	set("chat_msg", ({
		(: random_move :),
		"漁婦扯著沙啞的嗓子吆喝道﹕剛上岸的鮮魚活蝦哩﹐又肥又嫩﹐走過路過莫要錯過喲﹗\n",
		"漁婦挑著擔子﹐衝你咧嘴一笑﹕客官買尾魚罷﹖我家那口子今早纔打上來的﹐鮮著哩﹗\n",
		"漁婦嘆道﹕這幾日海上風浪大﹐出海的船少﹐魚價可漲了不少呢。\n",
	}));
	setup();
	carry_money("coin", 25);
}

int accept_fight()
{
	do_chat("漁婦把擔子一撂﹐雙手叉腰罵道﹕哪來的潑皮﹗光天化日想欺負人麼﹖衛兵﹗衛兵哪﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
