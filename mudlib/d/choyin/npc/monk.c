// monk.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("廟祝", ({"monk", "temple_keeper"}));
	set_race("human");
	set_class("commoner");
	set_level(6);

	set("age", 50);
	set("gender", "male");
	set("long",
		"一個身穿灰布道袍的廟祝﹐面容清瘦﹐神態安詳。他手持一把\n"
		"竹帚﹐不急不徐地打掃著廟前的落葉﹐偶爾停下來擦擦額頭的汗。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"廟祝雙手合十﹐唸道﹕善哉善哉。\n",
		"廟祝一邊掃地一邊嘆道﹕這落葉啊﹐掃也掃不完。\n",
		"廟祝說道﹕施主若要上香﹐自便就是。\n",
	}));
	setup();
	carry_money("coin", 15);
}
