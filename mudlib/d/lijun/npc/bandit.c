// bandit.c

#include <npc.h>

inherit F_FIGHTER;

void create()
{
	set_name("河匪", ({"bandit", "river_bandit"}));
	set_attr("str", 22);
	set_attr("con", 20);
	set_attr("dex", 20);
	set_race("human");
	set_class("fighter");
	set_level(25);

	set_skill("blade", 80);
	set_skill("dodge", 70);
	set_skill("parry", 60);

	set("age", 32);
	set("long",
		"一個面目兇惡的河匪﹐光著膀子﹐露出一身結實的肌肉。他的\n"
		"臉上有一道長長的刀疤﹐從左眉一直劃到右頰﹐更添了幾分凶悍。\n"
		"腰間別著一把鏽跡斑斑的朴刀﹐正虎視眈眈地盯著過路的行人。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"河匪陰笑道﹕此路是我開﹐此樹是我栽﹐要打此處過﹐留下買路財﹗\n",
		"河匪往地上吐了口唾沫﹐狠狠道﹕今天運氣不錯﹐又來了一個。\n",
	}));
	set("attitude", "aggressive");
	setup();
	carry_object( STOCK_WEAPON("broadsword") )->wield();
	carry_money("coin", 150);
}
