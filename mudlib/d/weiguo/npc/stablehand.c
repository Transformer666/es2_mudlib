// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("馬夫", ({"stablehand", "groom", "mafu"}));
	set_attr("str", 14);
	set_race("human");
	set_class("commoner");
	set_level(6);

	set_skill("unarmed", 10);

	set("age", 30);
	set("gender", "male");
	set("long",
		"一個穿著粗布衣裳的年輕人，正忙著給戰馬餵食和刷毛。他身上沾\n"
		"滿了乾草，和馬匹相處時動作十分溫柔，顯然對這些牲畜充滿了感情。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"馬夫輕輕拍了拍馬兒的脖子，柔聲說道：乖，吃飽了才有力氣。\n",
		"馬夫仔細檢查著馬蹄，嘀咕道：該換馬蹄鐵了……\n",
		"馬夫一邊梳理馬鬃一邊哼著小曲兒。\n",
	}));

	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
	carry_money("coin", 15);
}
