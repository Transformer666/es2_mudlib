// bandit.c

#include <npc.h>

inherit F_FIGHTER;

void create()
{
	set_name("松林盜匪", ({"bandit", "pine_bandit"}));
	set_attr("str", 16);
	set_attr("con", 14);
	set_attr("dex", 16);
	set_race("human");
	set_class("fighter");
	set_level(15);

	set_skill("blade", 50);
	set_skill("dodge", 40);
	set_skill("parry", 30);

	set("age", 28);
	set("long",
		"一個滿臉橫肉的盜匪﹐穿著一件打了好幾個補丁的短褂﹐腰間\n"
		"別著一把朴刀﹐一雙三角眼不住地打量著來往的行人﹐一看就不是\n"
		"什麼好東西。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"盜匪吆喝道﹕留下買路錢﹐饒你一條性命﹗\n",
		"盜匪往地上吐了口唾沫﹐嘿嘿冷笑。\n",
		"盜匪摸了摸腰間的朴刀﹐目露凶光。\n",
	}));
	set("aggressive", 1);
	setup();
	carry_object(__DIR__"obj/bandit_blade")->wield();
	carry_money("coin", 80);
}
