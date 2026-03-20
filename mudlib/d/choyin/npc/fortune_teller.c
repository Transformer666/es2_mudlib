// fortune_teller.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("算命先生", ({"fortune_teller", "teller"}));
	set_race("human");
	set_class("commoner");
	set_level(8);

	set("age", 55);
	set("gender", "male");
	set("long",
		"一個身穿青布長衫的老先生﹐頭戴方巾﹐手搖鵝毛扇﹐面前擺\n"
		"著一張小桌﹐桌上放著龜殼和銅錢。他鬚髮皆白﹐一雙眼睛卻精\n"
		"光四射﹐不時抬頭打量來往的行人﹐嘴裡唸唸有詞。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"算命先生搖著扇子說道﹕鐵口直斷﹐算盡天下事﹗來來來﹐算一卦﹗\n",
		"算命先生掐指一算﹐自言自語道﹕嗯﹐今日有貴人到此。\n",
		"算命先生撫了撫長鬚﹐若有所思。\n",
	}));
	setup();
	carry_money("coin", 50);
}
