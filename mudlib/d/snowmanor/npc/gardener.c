// gardener.c -- 雪吟莊後園的園丁（氣氛 NPC，受襲反擊）

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("園丁", ({ "gardener", "yuanding" }));
	set("nickname", "老園丁");
	set_attr("str", 19);
	set_attr("con", 19);
	set_race("human");
	set_class("commoner");
	set_level(10);

	set_skill("unarmed", 35);
	set_skill("dodge", 35);

	set("gender", "male");
	set("age", 55);
	set("long",
		"一名雪吟莊的老園丁﹐布衣芒鞋﹐腰間別著一把修枝的剪子﹐手\n"
		"指被泥土染得發黑。他佝著背在花木間慢慢侍弄﹐話極少﹐偶爾抬\n"
		"眼看你一下﹐又默默低下頭去﹐似是早已學會了在這莊上少說少問。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"園丁蹲在墨竹旁﹐一聲不響地修剪著枝葉。\n",
		"園丁低聲道﹕這園子裡的草木﹐莊主吩咐了﹐一片葉子也錯不得。\n",
		"園丁直起腰捶了捶背﹐望了望那四面高牆﹐又默默低下頭去。\n",
	}));
	setup();
	carry_object("/obj/area/obj/cloth")->wear();
	carry_money("coin", 20);
}

// 園丁雖是下人﹐被打也要拼命掙扎。結仇機制未實作﹐此處僅作自衛反擊。
int accept_fight(object ob)
{
	do_chat((: command, "say 你 ... 你要做甚﹖救命啊﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
