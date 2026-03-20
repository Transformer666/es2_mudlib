// NPC: /d/weiguo/npc/temple_keeper.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("廟祝", ({"temple_keeper", "keeper"}));
	set_race("human");
	set_class("commoner");
	set_level(8);

	set("age", 55);
	set("gender", "male");
	set("long",
		"一個身材瘦小的老者﹐穿著一件舊道袍﹐面容和善。他是這座城\n"
		"隍廟的廟祝﹐據說年輕時也曾是一名軍人﹐後來受了傷便留在廟裡\n"
		"照看香火。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"廟祝雙手合十﹕城隍爺保佑﹐邊關太平。\n",
		"廟祝嘆了口氣﹕老朽年輕時也是行伍中人啊。\n",
		"廟祝擦拭著香爐﹐嘴裡唸唸有詞。\n",
	}));

	setup();
	carry_money("coin", 20);
}
