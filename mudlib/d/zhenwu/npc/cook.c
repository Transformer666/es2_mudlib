// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("伙夫", ({"cook", "huofu"}));
	set_attr("str", 15);
	set_attr("con", 14);
	set_race("human");
	set_class("commoner");
	set_level(8);

	set_skill("unarmed", 15);

	set("age", 40);
	set("gender", "male");
	set("long",
		"一個壯實的伙夫正在灶台前忙碌著，額頭上掛著汗珠。他手持大鐵\n"
		"勺在鍋裡攪動著，粗糧燉肉的香氣瀰漫在整個伙房裡。軍營的飯食\n"
		"雖然粗糙，卻量大管飽。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"伙夫往鍋裡撒了把鹽，嘀咕道：幾百號人的飯，可不好伺候。\n",
		"伙夫擦了擦額頭上的汗，嚷道：今天的口糧又少了兩袋，這仗還讓不讓人吃飽了！\n",
		"伙夫翻動著鍋裡的肉，搖頭道：這批肉的成色可不怎麼樣……\n",
	}));

	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
	carry_money("coin", 20);
}
