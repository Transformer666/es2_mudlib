// beggar.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("老乞婆", ({"beggar", "old_beggar"}));
	set_race("human");
	set_class("commoner");
	set_level(5);

	set("age", 70);
	set("gender", "female");
	set("long",
		"一個衣衫襤褸的老婆婆﹐滿頭白髮亂蓬蓬的﹐臉上佈滿皺紋﹐\n"
		"手裡拄著一根破竹杖﹐身旁放著一個缺了口的碗。雖然看起來落魄\n"
		"不堪﹐但她的眼神卻異常清亮﹐似乎藏著什麼秘密。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"老乞婆咳嗽了幾聲﹐喃喃道﹕行行好吧﹐給口飯吃。\n",
		"老乞婆抬頭看了你一眼﹐嘴角露出一絲神秘的微笑。\n",
		"老乞婆自言自語道﹕這世道﹐不比從前了……\n",
	}));
	setup();
	carry_money("coin", 5);
}
