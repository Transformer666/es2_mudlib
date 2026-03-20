// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("練功師父", ({"weapon_master", "master", "shifu"}));
	set_attr("str", 22);
	set_attr("dex", 24);
	set_attr("con", 22);
	set_attr("int", 20);
	set_attr("spi", 20);
	set_attr("wis", 22);
	set_race("human");
	set_class("commoner");
	set_level(40);

	set_skill("sword", 80);
	set_skill("blade", 80);
	set_skill("pike", 80);
	set_skill("staff", 80);
	set_skill("unarmed", 80);
	set_skill("dodge", 70);
	set_skill("parry", 70);

	set("age", 60);
	set("gender", "male");
	set("long",
		"一位白髮蒼蒼但精神矍鑠的老者，他是這處修練場的管理者，精通\n"
		"各種兵器的基本功法，專門指導年輕武者練功。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"練功師父說道：練武之人，首重基本功。\n",
		"練功師父隨手抄起一柄木劍，演練了一套劍法。\n",
	}));
	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
}
