// fisherman.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("釣叟", ({"fisherman", "old_fisherman"}));
	set_attr("str", 12);
	set_attr("con", 16);
	set_attr("dex", 14);
	set_race("human");
	set_class("commoner");
	set_level(8);

	set("age", 65);
	set("long",
		"一個瘦削的老翁﹐頭戴斗笠﹐身披蓑衣﹐盤腿坐在河邊的大\n"
		"石頭上。他手持一根竹製釣竿﹐目不轉睛地盯著水面上的浮標﹐看\n"
		"起來已經在這裡坐了很久。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"釣叟輕聲說道﹕噓﹐小聲點﹐別嚇跑了魚。\n",
		"釣叟自言自語道﹕今天的魚兒不太上鉤啊。\n",
		"釣叟嘆了口氣﹕以前這裡的鯉魚又大又肥﹐現在越來越少了。\n",
		"釣叟忽然說道﹕聽說羿水深處有一條金色的大鯉魚﹐怕是成了精吧。\n",
	}));
	setup();
	carry_money("coin", 30);
}
