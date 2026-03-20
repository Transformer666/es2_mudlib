// farmer.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("農夫", ({"farmer", "lee_farmer"}));
	set_race("human");
	set_class("commoner");
	set_level(5);

	set("age", 35);
	set("gender", "male");
	set("long",
		"一個皮膚黝黑的農夫﹐穿著一件粗布短衣﹐褲腿捲到膝蓋以上﹐\n"
		"赤著雙腳站在田裡。他手裡拿著一把鋤頭﹐正在辛勤地勞作。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"農夫擦了擦汗﹐說道﹕今年的莊稼長得不錯﹐應該會有個好收成。\n",
		"農夫吆喝了一聲水牛﹐繼續埋頭幹活。\n",
	}));
	setup();
	carry_money("coin", 15);
}
