// NPC: /d/wenguo/npc/innkeeper.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("客棧老闆", ({"innkeeper", "keeper"}));
	set_race("human");
	set_class("commoner");
	set_level(8);

	set("age", 45);
	set("gender", "female");
	set("long",
		"一個衣著整潔的中年婦人﹐舉止落落大方。她把這間客棧打理得\n"
		"井井有條﹐從桌椅擺設到茶水飯食都一絲不苟﹐在縣城裡頗有口碑\n"
		"。她臉上總是帶著和善的笑容﹐讓旅客倍感親切。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"客棧老闆笑道﹕客倌﹐要住店還是喝杯茶﹖\n",
		"客棧老闆擦拭著桌面﹐嘴裡哼著小調。\n",
		"客棧老闆說道﹕我們這客棧雖然不大﹐但乾淨舒適﹐客倌儘管放心。\n",
	}));
	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
}
