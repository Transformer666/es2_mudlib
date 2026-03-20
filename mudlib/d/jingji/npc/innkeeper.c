// NPC: /d/jingji/npc/innkeeper.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("驛丞", ({"innkeeper", "yicheng"}));
	set_race("human");
	set_class("commoner");
	set_level(12);

	set("age", 50);
	set("gender", "male");
	set("long",
		"一位穿著官服的中年男子，面容嚴肅卻不失和氣。他是這間官方\n"
		"驛館的驛丞，負責接待來往的官員和使節。他舉止得體，說話不疾\n"
		"不徐，一看便知是在官場歷練多年的人物。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"驛丞整了整衣冠，恭敬地說道：客倌請安坐，茶水馬上就來。\n",
		"驛丞低聲吩咐小廝準備上等的龍井茶。\n",
	}));

	setup();
	carry_money("coin", 300);
	carry_object(STOCK_ARMOR("cloth"))->wear();
}
