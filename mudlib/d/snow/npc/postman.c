// NPC: /d/snow/npc/postman.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("驛站官員", ({"postman", "officer"}));
	set_attr("str", 12);
	set_attr("dex", 14);
	set_attr("con", 13);
	set_attr("int", 16);
	set_attr("wis", 15);
	set_attr("spi", 12);
	set_race("human");
	set_class("commoner");
	set_level(8);

	set("age", 32);
	set("gender", "male");
	set("long",
		"這位驛站官員穿著一身深藍色的公服﹐腰間掛著一串銅鑰匙和\n"
		"一個皮革信袋。他的眼神銳利而專注﹐不時低頭翻閱著手中的收\n"
		"發簿冊﹐偶爾抬頭望向門外﹐似乎在等待送信的快馬。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"驛站官員翻了翻手中的簿冊﹐喃喃自語道：這幾封信怎麼還沒到 ...\n",
		"驛站官員整理著架上的信件﹐神色頗為忙碌。\n",
		"驛站官員嘆了口氣﹐說道：最近路上不太平﹐信件常常延誤。\n",
	}));

	setup();
	carry_money("coin", 50);
	carry_object(STOCK_ARMOR("cloth"))->wear();
}

int accept_fight()
{
	do_chat("驛站官員皺眉道﹕這裡是驛站﹐請勿生事。\n");
	return 0;
}
