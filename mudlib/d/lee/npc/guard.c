// NPC: /d/lee/npc/guard.c

#include <npc.h>

inherit F_SOLDIER;

void create()
{
	set_name("村丁", ({"guard", "villager"}));
	set_race("human");
	set_class("fighter");
	set_level(10);

	set("age", 28);
	set("gender", "male");
	set_skill("staff", 45);
	set_skill("parry", 35);
	set_skill("dodge", 30);

	set("long",
		"一個年輕壯實的漢子﹐手持一根木棍﹐負責看守村口。他是村\n"
		"裡李老伯的侄子﹐雖然武藝不高﹐但為人忠厚﹐村民們都很信任他。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"村丁說道﹕咱們李家村雖小﹐可也不是隨便什麼人都能來的。\n",
		"村丁靠著大樹打了個哈欠。\n",
	}));

	setup();
	carry_object(STOCK_WEAPON("staff"))->wield();
	carry_money("coin", 20);
}
