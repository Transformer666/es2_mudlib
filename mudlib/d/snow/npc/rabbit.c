// rabbit.c -- 野兔，雪亭練功場附近的弱小獵物，給新手練手。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("野兔", ({ "rabbit", "yetu" }) );
	// 極低屬性：根骨 5 → 形體上限 25 點，遠弱於新手玩家。
	set_attr("con", 5);
	set_attr("str", 4);
	set_attr("dex", 2);
	set_race("human");
	set_class("commoner");
	set_level(1);

	// 練習用獵物：幾乎不閃躲，好讓零技巧的新手也打得中。
	set_skill("dodge", 0);

	set("age", 1);
	set("gender", "female");
	set("long",
		"一隻灰褐色的野兔﹐長長的耳朵警覺地豎著﹐一受驚便會四下\n"
		"亂竄。牠看起來十分瘦小﹐顯然不是什麼厲害的對手。\n");
	// 沿用 lieutenant.c 的經驗課目，數值極小。
	set("bounty/martial art", 5);
	set("bounty/martial mastery", 3);
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
