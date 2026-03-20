// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("老乞婆", ({"beggar_crone", "beggar", "crone"}));
	set_attr("str", 8);
	set_attr("dex", 10);
	set_attr("con", 8);
	set_attr("int", 14);
	set_attr("spi", 16);
	set_race("human");
	set_class("commoner");
	set_level(5);

	set("age", 70);
	set("gender", "female");
	set("long",
		"一個衣衫襤褸的老婦人，臉上佈滿了歲月的皺紋，但眼神中卻透著\n"
		"一股不凡的靈氣。她蜷縮在路邊，向過路的人伸出枯瘦的手。\n");
	set("chat_chance", 5);
	set("chat_msg", ({
		"老乞婆說道：行行好吧，給點吃的 ...\n",
		"老乞婆咳嗽了幾聲，裹了裹身上破爛的衣服。\n",
	}));
	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
}
