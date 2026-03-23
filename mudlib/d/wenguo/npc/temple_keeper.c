// NPC: /d/wenguo/npc/temple_keeper.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("廟祝", ({"temple keeper", "keeper"}));
	set_race("human");
	set_class("commoner");
	set_level(6);

	set("age", 65);
	set("gender", "male");
	set("long",
		"一個白髮蒼蒼的老者﹐身穿灰色布袍﹐手持一把竹掃帚。他是\n"
		"城隍廟的廟祝﹐負責日常的灑掃和焚香﹐在這座廟裡侍奉了大半輩\n"
		"子﹐對城隍爺的靈驗故事如數家珍。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"廟祝在神像前恭敬地上了一柱香。\n",
		"廟祝說道﹕城隍爺保佑﹐文國縣風調雨順﹐百姓安居。\n",
		"廟祝拿著掃帚﹐仔細地清掃著殿堂的每一個角落。\n",
	}));
	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
}
