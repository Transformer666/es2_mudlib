// NPC: /d/jingji/npc/innkeeper.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("驛丞", ({"innkeeper", "yicheng"}));
	set_race("human");
	set_class("commoner");
	set_level(12);

	set("age", 50);
	set("gender", "male");
	set("long",
		"一位穿著官服的中年男子，面容嚴肅卻不失和氣。他是這間官方\n"
		"驛館的驛丞，負責接待來往的官員和使節。他舉止得體，說話不疾\n"
		"不徐，一看便知是在官場歷練多年的人物。你可以用 list 看看\n"
		"有什麼﹐用 buy 來買。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"驛丞整了整衣冠，恭敬地說道：客倌請安坐，茶水馬上就來。\n",
		"驛丞低聲吩咐小廝準備上等的龍井茶。\n",
	}));
	set("merchandise", ([
		__DIR__"obj/longjing_tea" : 50,
		__DIR__"obj/steamed_bun" : 50,
	]));

	setup();
	carry_money("coin", 300);
	carry_object(STOCK_ARMOR("cloth"))->wear();
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
}

int accept_fight(object ob)
{
	do_chat("驛丞正色道﹕這裡是官驛﹐不可造次﹗\n");
	return 0;
}

void deliver_merchandise(object customer, mixed item)
{
	command("say " + item->name() + "﹐請用。");
	::deliver_merchandise(customer, item);
}
