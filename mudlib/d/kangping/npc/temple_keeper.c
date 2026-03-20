// NPC: /d/kangping/npc/temple_keeper.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("老廟祝", ({"temple_keeper", "keeper"}));
	set_race("human");
	set_class("commoner");
	set_level(6);

	set("age", 65);
	set("gender", "male");
	set("long",
		"一個佝僂著腰的老廟祝﹐頭髮花白﹐穿著一件洗得發白的灰布\n"
		"長衫。他手裡拿著一把竹帚﹐慢悠悠地打掃著廟裡的灰塵﹐嘴裡\n"
		"唸唸有詞。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"老廟祝嘆道﹕唉﹐這廟小﹐香火也少啊。\n",
		"老廟祝雙手合十﹐唸道﹕土地公保佑﹐風調雨順。\n",
		"老廟祝一邊掃地一邊自言自語。\n",
	}));

	setup();
	carry_money("coin", 10);
}
