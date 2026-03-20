// bandit_chief.c

#include <npc.h>

inherit F_FIGHTER;

void create()
{
	set_name("匪首", ({"bandit_chief", "chief"}));
	set_attr("str", 25);
	set_attr("con", 22);
	set_attr("dex", 22);
	set_race("human");
	set_class("fighter");
	set_level(30);

	set_skill("blade", 90);
	set_skill("dodge", 80);
	set_skill("parry", 70);

	set("age", 40);
	set("long",
		"老松寨的匪首﹐身材魁梧﹐虎背熊腰﹐一臉絡腮鬍子﹐兩眼精\n"
		"光四射。他穿著一件虎皮背心﹐手持一把寒光閃閃的大刀﹐渾身上\n"
		"下散發著一股凶悍之氣﹐看來是個殺人不眨眼的狠角色。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"匪首冷笑道﹕敢闖老松寨﹐是活膩了吧﹗\n",
		"匪首端起酒碗猛灌了一口﹐抹了抹嘴。\n",
		"匪首拍了拍手中的大刀﹐刀鋒閃著寒光。\n",
	}));
	set("attitude", "aggressive");
	setup();
	carry_object( STOCK_WEAPON("blade") )->wield();
	carry_object( STOCK_ARMOR("cloth") )->wear();
	carry_money("coin", 500);
}
