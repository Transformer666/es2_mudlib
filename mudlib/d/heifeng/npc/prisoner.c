// prisoner.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("被囚商人", ({"prisoner", "merchant"}));
	set_race("human");
	set_class("commoner");
	set_level(5);

	set("age", 40);
	set("long",
		"一個衣衫襤褸的商人﹐面容憔悴﹐身上有好幾處傷痕。他蜷縮\n"
		"在囚室的角落﹐看到有人來便用可憐巴巴的眼神望著你。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"商人哀求道﹕好漢﹐求求你救我出去﹐我一定重重酬謝﹗\n",
		"商人低聲說道﹕他們把我的貨物都搶走了……嗚嗚……\n",
		"商人嘆道﹕我是從喬陰來的商人﹐被這群強盜劫持到這裡已經三天了。\n",
	}));
	setup();
}
