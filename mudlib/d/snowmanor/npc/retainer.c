// retainer.c -- 雪吟莊家丁，巡弋於莊門與演武場（氣氛 NPC，受襲反擊）

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("雪吟莊家丁", ({ "retainer", "manor retainer", "jiading" }));
	set("nickname", "莊丁");
	set_attr("str", 21);
	set_attr("dex", 20);
	set_attr("con", 21);
	set_race("human");
	set_class("fighter");
	set_level(18);

	set_skill("blade", 65);
	set_skill("unarmed", 50);
	set_skill("parry", 55);
	set_skill("dodge", 55);
	set_skill("force", 45);

	set("gender", "male");
	set("age", 28);
	set("long",
		"一名雪吟莊的家丁﹐身著藏青勁裝﹐腰按一柄單刀﹐站得筆直如\n"
		"松。他眼神警惕﹐神情肅然﹐將過往的人一一打量﹐顯是受過嚴格\n"
		"操練﹐絕非尋常看門的莊客。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"家丁按著腰間單刀﹐警惕地將你上下打量了一番。\n",
		"家丁沉聲道﹕莊上自有莊上的規矩﹐客人好自為之。\n",
		"家丁挺直了腰板﹐目不斜視地巡看著四下動靜。\n",
	}));
	setup();
	carry_object("/obj/area/obj/blade")->wield();
	carry_object("/obj/area/obj/cloth")->wear();
	carry_money("coin", 60);
}

// 莊丁護院﹐受襲必還手。結仇機制未實作﹐此處僅作自衛反擊。
int accept_fight(object ob)
{
	do_chat((: command, "say 大膽﹗竟敢在雪吟莊撒野﹗來人哪﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
