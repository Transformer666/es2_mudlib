// NPC: /d/chixiao/npc/temple_keeper.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("老廟祝", ({"temple_keeper", "keeper"}));
	set_race("human");
	set_class("commoner");
	set_level(6);

	set("age", 70);
	set("gender", "male");
	set("long",
		"一個枯瘦如柴的老廟祝﹐一雙混濁的眼睛深陷在眼窩裡﹐卻不\n"
		"時閃過一絲精光。他穿著一件破舊的灰色道袍﹐手裡拿著一串念\n"
		"珠﹐嘴裡不停地唸著什麼。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"老廟祝搖頭嘆道﹕這村子的邪氣太重了﹐城隍爺也鎮不住啊。\n",
		"老廟祝雙手合十﹐唸道﹕城隍爺保佑﹐驅邪避凶。\n",
		"老廟祝壓低聲音說﹕村子北邊那個池子﹐千萬別亂碰。\n",
	}));

	setup();
	carry_money("coin", 10);
}
