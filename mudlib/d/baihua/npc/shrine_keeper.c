// NPC: /d/baihua/npc/shrine_keeper.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("祠堂婆婆", ({"shrine_keeper", "keeper"}));
	set_race("human");
	set_class("commoner");
	set_level(5);

	set("age", 70);
	set("gender", "female");
	set("long",
		"一個滿頭銀髮的老婆婆﹐穿著一件素淨的藍花布衫。她是百花\n"
		"村祠堂的看守人﹐每天按時上香、擺放供品﹐把祠堂打掃得纖塵\n"
		"不染。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"婆婆輕輕拂去供桌上的灰塵﹐換上一盤新摘的鮮花。\n",
		"婆婆雙手合十﹐對著牌位喃喃祝禱。\n",
		"婆婆望著牆上那幅仙女畫卷﹐露出慈祥的微笑。\n",
	}));

	setup();
	carry_money("coin", 8);
}
