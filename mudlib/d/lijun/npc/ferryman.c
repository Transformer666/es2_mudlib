// ferryman.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("老艄公", ({"ferryman", "boatman"}));
	set_attr("str", 16);
	set_attr("con", 20);
	set_attr("dex", 14);
	set_race("human");
	set_class("commoner");
	set_level(12);

	set("age", 60);
	set("long",
		"一個鬚髮皆白的老艄公﹐皮膚被日曬雨淋得黝黑粗糙﹐雙手\n"
		"佈滿老繭。他穿著一件洗得發白的粗布短衫﹐腰間繫著一條草繩﹐\n"
		"赤著雙腳站在船頭﹐一副見慣了風浪的模樣。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"老艄公撐著竹篙﹐說道﹕這羿水啊﹐看著平靜﹐底下暗流可凶著呢。\n",
		"老艄公吸了口旱煙﹐吐出一口煙圈﹐望著河面出神。\n",
		"老艄公說道﹕要過河的趕緊﹐等下起風就不好擺渡了。\n",
		"老艄公哼著不知名的漁歌﹐手中的竹篙有節奏地點著水面。\n",
	}));
	setup();
	carry_money("coin", 80);
}
