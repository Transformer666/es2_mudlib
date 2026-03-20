// NPC: /d/longan/npc/storyteller.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("說書人", ({"storyteller", "old_man"}));
	set_race("human");
	set_class("commoner");
	set_level(8);

	set_skill("unarmed", 20);

	set("age", 60);
	set("long",
		"一位鬚髮斑白的老者，身穿褪色的灰布長衫，手持一把摺扇。他\n"
		"坐在廣場角落的石凳上，繪聲繪色地講述著江湖上的奇聞軼事，周\n"
		"圍聚攏了不少聽眾。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"說書人一拍醒木，朗聲道：話說當年天邪國一戰，那可是驚天動地！\n",
		"說書人搖著摺扇，笑道：列位看倌，且聽下回分解。\n",
		"說書人呷了口茶，清了清嗓子，繼續說道：卻說那封山派的劍法……\n",
		"說書人嘆道：江湖險惡，世事難料啊。\n",
	}));

	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
	carry_money("coin", 50);
}
