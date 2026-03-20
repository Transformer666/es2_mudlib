// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("馬夫", ({"stablehand", "groom", "mafu"}));
	set_attr("str", 13);
	set_race("human");
	set_class("commoner");
	set_level(6);

	set_skill("unarmed", 10);

	set("age", 25);
	set("gender", "male");
	set("long",
		"一個年輕的馬夫正忙著給馬匹添加草料，他的身上沾滿了乾草和馬\n"
		"毛。這些戰馬都是精挑細選的良駒，在他的悉心照料下一匹匹毛色油\n"
		"亮，精神抖擻。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"馬夫輕輕撫摸著馬兒的鬃毛，柔聲道：好傢伙，今天精神不錯啊。\n",
		"馬夫仔細檢查著馬蹄，自言自語道：蹄鐵磨得差不多了，得找鐵匠換一副。\n",
		"馬夫指著一匹棗紅馬笑道：這匹叫「追風」，跑起來快得很吶！\n",
	}));

	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
	carry_money("coin", 10);
}
