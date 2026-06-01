// barman.c -- 錢記酒樓的酒保（F_VENDOR 供應酒食﹐沿用既有食物物件 + 本地滷味）。
//             兼斐縣非戰鬥支線「悅客來的散帳」的一處核帳點：玩家持悅客來
//             客棧掌櫃的收帳冊來核錢記酒樓代記的賒帳（ask barman about 賒帳）。
//             僅推進該支線旗標（quest/feixian_tab_tavern / _count）﹐不給賞、
//             不動別的任務旗標﹐核帳一次即記﹐重問不重複計數。

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

	// 賒帳：非戰鬥支線「悅客來的散帳」的核帳點（須已接任務、且持收帳冊在身）
	if( arg == "barman about 賒帳"
	||  arg == "barman about 散帳"
	||  arg == "barman about 收帳冊"
	||  arg == "barman about 帳"
	||  arg == "barman about tab" ) {
		object me = this_player();

		// 未接任務 / 已交差：只當尋常打聽，不核帳、不記旗標
		if( me->query("quest/feixian_tab") != 1 ) {
			do_chat((: command,
				"say 賒帳﹖客官打聽這個做甚﹖咱錢記是有幾位相熟的客商記在悅客來帳上的酒飯錢﹐都是老相與了﹐客官若不是掌櫃打發來核帳的﹐這帳本酒保可不便給生人看。" :));
			return 1;
		}

		// 接了任務卻沒帶收帳冊：提示先去掌櫃處領冊
		if( !present("tab ledger", me) ) {
			do_chat((: command,
				"say 客官是悅客來掌櫃打發來核帳的﹖那得先問掌櫃討了那本收帳冊來﹐酒保纔好對著謄錄。空著手﹐這帳可沒法核。" :));
			return 1;
		}

		// 已核過本家：純氣氛，不重複計數
		if( me->query("quest/feixian_tab_tavern") ) {
			do_chat((: command,
				"say 錢記這幾筆酒帳﹐方纔已替客官核對謄錄在收帳冊上了。客官且去清風茶行、雜貨鋪那兩處﹐把另兩家的也核齊了罷。" :));
			return 1;
		}

		// 首次核帳：記本家旗標、總數 +1
		me->set("quest/feixian_tab_tavern", 1);
		me->add("quest/feixian_tab_count", 1);
		do_chat(({
			(: command, "say 哦﹐掌櫃打發客官來核散帳的﹖難為他還記掛著這幾筆。客官把收帳冊攤開﹐酒保這就把錢記代記的賒帳給客官念。" :),
			(: command, "say 城南來的綢緞客賒過三回女兒紅、兩碟滷味﹐城北那走鏢的賒過一頓酒飯——都記在悅客來帳上的。酒保替客官一筆筆對著謄錄清楚了﹐客官收好冊子﹐再去別家核罷。" :),
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
