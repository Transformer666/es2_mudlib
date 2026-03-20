// bandit.c

#include <npc.h>

inherit F_FIGHTER;

void create()
{
	set_name("黑風寨匪徒", ({"bandit", "heifeng_bandit"}));
	set_attr("str", 20);
	set_attr("con", 18);
	set_attr("dex", 18);
	set_race("human");
	set_class("fighter");
	set_level(20);

	set_skill("axe", 65);
	set_skill("dodge", 55);
	set_skill("parry", 45);

	set("age", 30);
	set("long",
		"一個黑風寨的匪徒﹐穿著一件黑色短褂﹐腰間掛著一把鐵斧。\n"
		"他滿臉橫肉﹐兩眼凶光畢露﹐一看便知不是善類。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"匪徒嘿嘿冷笑道﹕又來了一個送死的。\n",
		"匪徒拍了拍腰間的鐵斧﹐神色得意。\n",
	}));
	set("attitude", "aggressive");
	setup();
	carry_object(__DIR__"obj/iron_axe")->wield();
	carry_money("coin", 120);
}
