// sentry.c -- 檒城衛兵所裡當值的衛兵（純氣氛 NPC）

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("衛兵", ({ "sentry", "guard", "fancheng guard" }) );
	set_attr("str", 19);
	set_attr("con", 18);
	set_race("human");
	set_class("fighter");
	set_level(12);

	set_skill("blade", 45);
	set_skill("parry", 40);
	set_skill("dodge", 35);
	set_skill("unarmed", 35);

	set("age", 28);
	set("gender", "male");
	set("long",
		"一個檒城的衛兵﹐曬得黝黑精壯﹐穿著繡了「勇」字的號褂﹐\n"
		"腰間挎著一柄腰刀。他原也是本地討海人家的子弟﹐投了軍﹐\n"
		"這會兒按刀立在衛兵所裡﹐警惕地打量著進出的生面孔﹐倒有\n"
		"幾分公門中人的派頭。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		"衛兵按著刀柄﹐沉聲道﹕外鄉人到了檒城﹐安分守己便好。\n",
		"衛兵擦拭著腰刀﹐頭也不抬地斜睨了你一眼。\n",
		"衛兵壓低聲音道﹕統領這幾日盯得緊﹐外海的海寇不安分﹐城裡也得提防著奸細。\n",
	}));
	setup();
	carry_object( STOCK_WEAPON("broadsword") )->wield();
	carry_money("coin", 60);
}

void init()
{
	::init();
	if( !is_fighting() )
		do_chat((: command, "say 站住﹗到衛兵所來何事﹖" :));
}

int accept_fight(object ob)
{
	do_chat("衛兵厲聲喝道﹕好大的膽子﹗竟敢在衛兵所裡動手﹗來人哪﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
