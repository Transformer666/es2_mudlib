// villager.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("村民", ({"villager", "kangping_villager"}));
	set_race("human");
	set_class("commoner");
	set_level(5);

	set("age", 35);
	set("gender", "male");
	set("long", "一個樸實的農家漢子﹐皮膚被太陽曬得黝黑﹐手裡扛著一把鋤頭。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"村民嘆了口氣﹐說道﹕今年的收成不太好啊。\n",
		"村民說道﹕松林裡的土匪越來越猖狂了﹐出門都不安全。\n",
		"村民看了看天色﹐自言自語道﹕該回去餵雞了。\n",
	}));
	setup();
	carry_money("coin", 15);
}
