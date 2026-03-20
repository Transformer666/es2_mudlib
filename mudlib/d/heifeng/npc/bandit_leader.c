// bandit_leader.c

#include <npc.h>

inherit F_FIGHTER;

void create()
{
	set_name("黑風寨主", ({"bandit_leader", "leader", "chief"}));
	set_attr("str", 30);
	set_attr("con", 28);
	set_attr("dex", 25);
	set_race("human");
	set_class("fighter");
	set_level(40);

	set_skill("axe", 110);
	set_skill("dodge", 90);
	set_skill("parry", 85);
	set_skill("internal", 60);

	set("age", 45);
	set("long",
		"黑風寨的寨主﹐身材高大魁梧﹐一臉絡腮鬍子﹐雙目如電。他\n"
		"穿著一件黑色虎皮大氅﹐手持一把沉重的開山大斧﹐渾身散發著一\n"
		"股凜然的殺氣﹐令人不敢直視。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"寨主仰天大笑道﹕哈哈哈﹐天下英雄﹐誰敢與我一戰﹗\n",
		"寨主端起酒碗一飲而盡﹐往地上一摔﹐碗碎了一地。\n",
		"寨主冷冷地掃視著四周﹐目光所到之處﹐匪徒們紛紛低頭。\n",
	}));
	set("attitude", "aggressive");
	setup();
	carry_object( STOCK_WEAPON("broadaxe") )->wield();
	carry_object(__DIR__"obj/bandit_armor")->wear();
	carry_money("coin", 800);
}
