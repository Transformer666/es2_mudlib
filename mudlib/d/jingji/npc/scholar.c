// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("書生", ({"scholar", "student", "shusheng"}));
	set_race("human");
	set_class("commoner");
	set_level(12);
	set("age", 25);
	set("gender", "male");
	set_attr("int", 18);
	set_attr("wis", 16);
	set_skill("unarmed", 15);
	set_skill("dodge", 20);
	set("long",
		"一名身著儒衫的年輕書生，正在書院中勤奮苦讀。他口中低聲\n"
		"吟誦著經典，手中毛筆不停地在書卷上做著批註。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"書生搖頭晃腦地誦讀道：大學之道，在明明德，在親民，在止於至善……\n",
		"書生嘆了口氣道：今年的科舉將近，還有許多書卷未曾讀完。\n",
		"書生翻開一卷論語，喃喃道：學而時習之，不亦說乎……\n",
	}));

	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
	carry_money("coin", 40);
}

int accept_fight(object ob)
{
	do_chat("書生慌張地說道：君子動口不動手，有話好好說！\n");
	return 0;
}
