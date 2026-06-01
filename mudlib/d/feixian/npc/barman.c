// barman.c -- 錢記酒樓的酒保（F_VENDOR 供應酒食﹐沿用既有食物物件 + 本地滷味）

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

int do_ask(string arg);

void create()
{
	set_name("酒保", ({ "barman", "feixian_barman", "waiter" }) );
	set("nickname", "酒保");
	set_race("human");
	set_class("commoner");
	set_level(3);

	set("age", 23);
	set("gender", "male");
	set("long",
		"一個眼明手快的後生酒保﹐肩上搭著條油亮的抹布﹐一手提著\n"
		"錫酒壺﹐一手托著菜盤﹐在桌椅間穿梭如飛。他生就一張能說會\n"
		"道的嘴﹐報起菜名酒名來脆生生的﹐惹得滿堂酒客都樂。你可以\n"
		"用 list 看櫃上有些什麼酒食﹐用 buy 向他點來吃。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"酒保提著錫壺脆生生地吆喝﹕客官裡邊坐﹗女兒紅、狀元紅、滷味乾貨﹐要點甚麼只管招呼一聲﹗\n",
		"酒保麻利地替客人篩著熱酒﹐口中還不住地報著菜名﹐忙得腳不沾地。\n",
		"酒保抹了把汗笑道﹕咱錢記酒樓在這斐縣城裡﹐可是掛了號的老字號哩﹗\n",
	}));
	// 酒樓供應酒食﹐沿用既有食物物件﹐另搭本地自製的滷味與酒釀圓子。
	set("merchandise", ([
		"/d/feixian/obj/braise" : 1,
		"/d/feixian/obj/tangyuan" : 1,
		"/obj/food/pork" : 40,
		"/obj/food/manto" : 50,
		"/obj/food/dumpling" : 50,
	]));

	setup();
	carry_money("coin", 120);
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
	add_action("do_ask", "ask");
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問酒保些甚麼﹖（試試 ask barman about 斐縣）\n");

	if( arg == "barman about 斐縣"
	||  arg == "barman about 錢記"
	||  arg == "barman about 酒樓"
	||  arg == "barman about feixian" ) {
		do_chat(({
			(: command, "say 客官是頭一回到斐縣罷﹖咱這小縣城別的沒有﹐就五向路口那五條道岔得新鮮﹐外鄉人來了十個有九個要在路碑前轉上半晌哩。" :),
			(: command, "say 咱錢記的女兒紅是自家窖裡埋足了年頭的﹐配上後堂那鍋老滷﹐管教客官吃了還想再來。" :),
		}));
		return 1;
	}

	return notify_fail("酒保忙著張羅酒菜﹐衝你憨憨一笑﹕客官先點些甚麼罷﹖\n");
}

int accept_fight(object ob)
{
	do_chat("酒保嚇得縮起脖子賠笑﹕客官息怒﹗小的這就給您換桌好酒﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
