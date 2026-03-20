// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("江述仁", ({"jiang_shuren", "jiang", "shuren"}));
	set_attr("str", 12);
	set_attr("dex", 16);
	set_attr("con", 14);
	set_attr("int", 24);
	set_attr("spi", 22);
	set_attr("wis", 20);
	set_race("human");
	set_class("commoner");
	set_level(25);

	set_skill("unarmed", 30);
	set_skill("dodge", 40);

	set("age", 45);
	set("gender", "male");
	set("long",
		"江述仁是龍圖丹派的醫師，擅長煉丹製藥。他看起來約四十五歲，\n"
		"一身青袍，神情略顯疲憊，似乎最近欠了不少藥材的債。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"江述仁嘆了口氣，說道：唉，我這次可是欠了不少啊 ...\n",
		"江述仁翻閱著手中的藥方，眉頭緊鎖。\n",
	}));
	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
}
