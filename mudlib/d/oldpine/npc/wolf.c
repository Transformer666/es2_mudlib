// wolf.c

#include <npc.h>

inherit F_FIGHTER;

void create()
{
	set_name("野狼", ({"wolf", "wild_wolf"}));
	set_attr("str", 14);
	set_attr("con", 12);
	set_attr("dex", 18);
	set_race("animal");
	set_class("fighter");
	set_level(12);

	set_skill("unarmed", 55);
	set_skill("dodge", 50);

	set("age", 6);
	set("long",
		"一匹灰毛野狼﹐體型不小﹐兩眼泛著綠光﹐嘴裡露出尖銳的\n"
		"獠牙﹐不時發出低沉的嗚嗚聲﹐看來正處於警戒狀態。\n");
	set("attitude", "aggressive");
	setup();
	carry_money("coin", 30);
}
