// mountain_wolf.c

#include <npc.h>

inherit F_FIGHTER;

void create()
{
	set_name("山狼", ({"mountain_wolf", "wolf"}));
	set_attr("str", 20);
	set_attr("con", 18);
	set_attr("dex", 22);
	set_race("animal");
	set_class("fighter");
	set_level(12);

	set_skill("unarmed", 50);
	set_skill("dodge", 45);

	set("age", 6);
	set("gender", "male");
	set("long",
		"一隻灰褐色的山狼﹐體型比普通狼要大上一圈。它的毛皮粗糙\n"
		"而蓬亂﹐一雙銳利的黃色眼睛透著凶光﹐嘴角露出鋒利的獠牙﹐\n"
		"低沉的喉音中透著危險的警告。\n");
	set("attitude", "aggressive");
	setup();
	carry_money("coin", 30);
}
