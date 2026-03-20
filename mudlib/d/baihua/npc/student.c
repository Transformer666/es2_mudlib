// student.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("小學童", ({"student", "child"}));
	set_race("human");
	set_class("commoner");
	set_level(2);

	set("age", 8);
	set("gender", "male");
	set("long",
		"一個穿著藍布小褂的孩子﹐手裡捧著一冊書﹐搖頭晃腦地背誦\n"
		"著什麼。看到有人走過便抬起頭來﹐露出天真無邪的笑容。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"小學童搖頭晃腦地背誦道﹕人之初﹐性本善……\n",
		"小學童好奇地看著你﹐問道﹕你認得字嗎﹖\n",
		"小學童蹲在地上用樹枝寫字﹐一筆一劃十分認真。\n",
	}));
	setup();
}
