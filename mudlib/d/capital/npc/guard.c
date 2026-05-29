// guard.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("禁軍衛士", ({ "guard", "jinjun" }) );
	set_attr("str", 24);
	set_attr("con", 22);
	set_race("human");
	set_class("fighter");
	set_level(20);

	set_skill("sword", 65);
	set_skill("parry", 55);
	set_skill("dodge", 50);
	set_skill("unarmed", 45);

	set("age", 30);
	set("gender", "male");
	set("long",
		"一名鎮守京畿城門的禁軍衛士﹐身披一副亮銀的鎖子甲﹐外罩繡\n"
		"著金線的紅戰袍﹐腰懸長劍﹐按劍肅立。他身形挺拔如松﹐目光\n"
		"如電﹐渾身透著一股久經操練的彪悍與帝都禁衛的森嚴氣派。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		"禁軍衛士按著劍柄﹐目光如鷹隼般掃過進出城門的人流。\n",
		"禁軍衛士挺直了腰板﹐沉聲道﹕京畿重地﹐爾等須得安分守己。\n",
		"禁軍衛士低聲道﹕近來後海湖一帶不甚太平﹐入夜後莫往湖邊去。\n",
	}));
	setup();
	carry_object( STOCK_WEAPON("longsword") )->wield();
	carry_money("coin", 200);
}

void init()
{
	::init();
	if( !is_fighting() )
		do_chat((: command, "say 站住﹗進京者﹐可有路引﹖" :));
}

int accept_fight(object ob)
{
	do_chat("禁軍衛士厲喝一聲﹕大膽﹗竟敢在天子腳下行兇﹗來人哪﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
