// vim: syntax=lpc

#include <npc.h>

inherit F_FIGHTER;

void create()
{
	set_name("退伍老兵", ({"old soldier", "old_soldier", "soldier"}));
	set_attr("str", 22);
	set_attr("con", 20);
	set_attr("dex", 16);
	set_attr("int", 14);
	set_attr("spi", 12);
	set_race("human");
	set_class("fighter");
	set_level(25);

	set_skill("sword", 80);
	set_skill("dodge", 60);
	set_skill("parry", 70);
	set_skill("force", 40);

	set("age", 52);
	set("gender", "male");
	set("long",
		"一個身材高大的中年漢子﹐臉上有一道長長的刀疤﹐從左額\n"
		"一直延伸到右頰。他穿著一件洗得發白的舊軍服﹐腰間掛著\n"
		"一把保養得鋥亮的長刀。據說他年輕時在振武軍營服過役﹐\n"
		"退伍後回到村子﹐義務教村裡的年輕人一些防身的功夫。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"老兵揮了幾下刀﹐刀風呼嘯﹐虎虎生威。\n",
		"老兵說道﹕練武不為逞兇鬥狠﹐只求保家衛民。\n",
		"老兵摸了摸臉上的刀疤﹐眼中閃過一絲追憶。\n",
		"老兵沉聲道﹕那年在北方打仗﹐我們一個營三百人﹐最後只回來了二十七個。\n",
	}));
	setup();
	carry_object(STOCK_WEAPON("longsword"))->wield();
	carry_object(STOCK_ARMOR("cloth"))->wear();
	carry_money("coin", 80);
}
