// NPC: /d/city/npc/beggar.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("乞丐", ({"beggar"}));
	set_race("human");
	set_class("commoner");
	set_level(2);

	set("age", 55);
	set("long",
		"一個衣衫襤褸的老乞丐蜷縮在牆角，面前擺著一個破碗。\n"
		"他蓬頭垢面，但眼神中卻透著一絲不尋常的精光。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"乞丐有氣無力地說：行行好，賞口飯吃吧……\n",
		"乞丐低頭打了個盹，又猛然驚醒。\n",
	}));

	setup();
	carry_money("coin", 5);
}
