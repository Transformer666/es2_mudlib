// NPC: /d/city/npc/peddler.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("小販", ({"peddler", "hawker"}));
	set_race("human");
	set_class("commoner");
	set_level(3);

	set("age", 28);
	set("long",
		"一個年輕的小販，挑著擔子在市集裡兜售各種小吃和雜貨。\n"
		"他嗓門很大，吆喝聲響徹整個市集。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"小販扯著嗓子喊道：糖葫蘆嘞——又甜又脆的糖葫蘆！\n",
		"小販吆喝道：熱騰騰的肉包子，剛出籠的！\n",
	}));

	setup();
	carry_money("coin", 30);
}
