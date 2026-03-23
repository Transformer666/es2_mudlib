// NPC: /d/wenguo/npc/guard.c

#include <npc.h>

inherit F_SOLDIER;

void create()
{
	set_name("縣城守衛", ({"guard", "city guard"}));
	set_race("human");
	set_class("fighter");
	set_level(14);

	set("age", 25);
	set("gender", "male");
	set("long",
		"一個身穿輕甲的縣城守衛﹐腰佩長劍﹐站姿挺拔。他的裝備比\n"
		"一般村鎮的守衛要精良許多﹐臂上繡著文國縣的標記﹐目光銳利地\n"
		"注視著過往的行人。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"縣城守衛目光掃過四周﹐警惕地觀察著來往行人。\n",
		"縣城守衛說道﹕文國縣治安良好﹐各位安心通行。\n",
		"縣城守衛整了整身上的甲冑﹐挺直了腰桿。\n",
	}));
	setup();
	carry_object(STOCK_WEAPON("longsword"))->wield();
	carry_object(STOCK_ARMOR("cloth"))->wear();
	carry_money("coin", 40);
}
