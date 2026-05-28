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

	set("age", 33);
	set("gender", "male");
	set("long",
		"一個縣衙的差役﹐頭戴紅纓暖帽﹐身穿一件繡著「勇」字的號\n"
		"褂﹐腰間挎著一柄繡春刀﹐手裡端著根水火棍﹐神色倨傲地巡視\n"
		"著四下﹐一副公門中人的派頭。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		"差役把水火棍往地上一頓﹐喝道﹕閒雜人等﹐莫要在縣衙前逗留﹗\n",
		"差役斜睨著你﹐冷哼一聲﹐顯是沒把你這外鄉人放在眼裡。\n",
		"差役說道﹕縣太爺三日後便要升堂審那夥老松寨的案子﹐城裡可熱鬧了。\n",
	}));
	setup();
	carry_object( STOCK_WEAPON("broadsword") )->wield();
	carry_money("coin", 80);
}

void init()
{
	::init();
	if( !is_fighting() )
		do_chat((: command, "say 哪裡來的生面孔﹖到縣城來﹐可得安分些﹗" :));
}

int accept_fight(object ob)
{
	do_chat("差役厲聲喝道﹕好大的膽子﹗竟敢在縣衙前撒野﹗來人哪﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
