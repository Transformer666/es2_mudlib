// runner.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("差役", ({ "runner", "yamen runner", "chaiyi" }) );
	set_attr("str", 20);
	set_attr("con", 18);
	set_race("human");
	set_class("fighter");
	set_level(12);

	set_skill("blade", 45);
	set_skill("parry", 40);
	set_skill("dodge", 35);
	set_skill("unarmed", 35);

	set("age", 35);
	set("gender", "male");
	set("long",
		"一個風城衙門的差役﹐頭戴暖帽﹐身披一件繡著「勇」字的羊\n"
		"皮號褂﹐腰間挎著一柄彎刀﹐手裡端著根水火棍﹐在茶樓裡一邊\n"
		"吃茶﹐一邊警惕地打量著南來北往的生面孔﹐一副公門中人的派\n"
		"頭。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		"差役把水火棍往地上一頓﹐喝道﹕外鄉人到了風城﹐可得安分守己﹗\n",
		"差役斜睨著你﹐冷哼一聲﹐顯是沒把你這南邊來的客人放在眼裡。\n",
		"差役壓低聲音道﹕近來塞外的馬賊鬧得兇﹐衙門已調了人手上城頭戒備﹐城裡盤查得緊。\n",
	}));
	setup();
	carry_object( STOCK_WEAPON("broadsword") )->wield();
	carry_money("coin", 80);
}

void init()
{
	::init();
	if( !is_fighting() )
		do_chat((: command, "say 哪裡來的生面孔﹖到風城來﹐可得規矩些﹗" :));
}

int accept_fight(object ob)
{
	do_chat("差役厲聲喝道﹕好大的膽子﹗竟敢在風城撒野﹗來人哪﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
