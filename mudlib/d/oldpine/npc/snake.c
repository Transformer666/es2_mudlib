// snake.c

#include <npc.h>

inherit F_FIGHTER;

void create()
{
	set_name("毒蛇", ({"snake", "viper"}));
	set_attr("str", 10);
	set_attr("con", 8);
	set_attr("dex", 20);
	set_race("animal");
	set_class("fighter");
	set_level(10);

	set_skill("unarmed", 50);
	set_skill("dodge", 60);

	set("age", 5);
	set("long",
		"一條渾身佈滿花紋的毒蛇﹐約有三尺來長﹐三角形的蛇頭不停\n"
		"地吐著猩紅的蛇信﹐一雙冰冷的眼睛死死地盯著你﹐隨時準備發\n"
		"動攻擊。\n");
	set("aggressive", 1);
	setup();
	carry_money("coin", 20);
}
