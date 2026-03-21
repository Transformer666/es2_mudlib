// snow_leopard.c

#include <npc.h>

inherit F_FIGHTER;

void create()
{
	set_name("雪豹", ({"snow_leopard", "leopard"}));
	set_attr("str", 28);
	set_attr("con", 24);
	set_attr("dex", 26);
	set_race("animal");
	set_class("fighter");
	set_level(18);

	set_skill("unarmed", 70);
	set_skill("dodge", 60);
	set_skill("parry", 35);

	set("age", 9);
	set("gender", "female");
	set("long",
		"一頭威猛的雪豹﹐渾身覆蓋著灰白色帶有黑色斑點的厚實皮毛。\n"
		"它的身軀矯健有力﹐粗壯的尾巴幾乎與身體等長。一雙碧綠的眼\n"
		"睛透著冷酷的殺意﹐正無聲地注視著你的一舉一動。\n");
	set("attitude", "aggressive");
	setup();
	carry_money("coin", 70);
}
