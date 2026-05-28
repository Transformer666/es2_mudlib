// mouse.c -- 田鼠，雪亭練功場旁的弱小獵物，會咬人但傷害極微。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("田鼠", ({ "mouse", "tianshu" }) );
	// 極低屬性：根骨 4 → 形體上限 20 點，比新手玩家弱得多。
	set_attr("con", 4);
	set_attr("str", 5);
	set_attr("dex", 2);
	set_race("human");
	set_class("commoner");
	set_level(1);

	// 練習獵物：幾乎不閃躲，零技巧新手也打得中。
	set_skill("unarmed", 1);
	set_skill("dodge", 0);

	set("age", 1);
	set("gender", "male");
	set("long",
		"一隻肥肥的田鼠﹐露著兩顆門牙﹐在草叢裡鑽進鑽出。被逼急\n"
		"了牠也會張口亂咬﹐不過那點力氣連抓破皮都難。\n");
	// 沿用 lieutenant.c 的經驗課目，數值極小。
	set("bounty/martial art", 6);
	set("bounty/martial mastery", 3);
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
