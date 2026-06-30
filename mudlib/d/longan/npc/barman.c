// barman.c -- 無腸酒店的酒保（F_VENDOR 供應龍安米酒與下酒菜）。
//             鏡 d/feixian/npc/barman.c 之 F_VENDOR 範式。

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

int do_ask(string arg);

void create()
{
	set_name("酒保", ({ "barman", "longan_barman", "waiter" }) );
	set("nickname", "酒保");
	set_race("human");
	set_class("commoner");
	set_level(3);

	set("age", 21);
	set("gender", "male");
	set("long",
		"一個眼明手快的後生酒保﹐挽著袖子﹐肩上搭條油亮的抹布﹐一\n"
		"手提著錫酒壺﹐一手托著菜盤﹐在臨水的桌椅間穿梭如飛。他生就\n"
		"一張能說會道的嘴﹐報起菜名酒名來脆生生的。你可以用 list 看\n"
		"櫃上有些什麼酒食﹐用 buy 向他點來吃。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"酒保提著錫壺脆生生地吆喝﹕客官裡邊坐﹗龍安米酒、糟魚醉蝦﹐要點甚麼只管招呼一聲﹗\n",
		"酒保麻利地替客人篩著熱酒﹐口中還不住地報著菜名﹐忙得腳不沾地。\n",
		"酒保抹了把汗笑道﹕咱這龍安米酒﹐聞香下馬﹐連那位無腸老先生都離不得哩﹗\n",
	}));
	// 無腸酒店供應自釀米酒、本地下酒菜﹐另搭幾樣尋常酒食。
	set("merchandise", ([
		// 注意：merchandise 路徑須為「可載入的正規路徑」——driver 不正規化 `../`，
		// 故不可用 __DIR__"../obj/..."(會解成 /d/longan/npc/../obj/...、載入失敗，
		// 連帶 do_vendor_list/affirm_merchandise 整個 foreach 報錯、list/buy 全失效)。
		// 一律用 /d/longan/obj/... 絕對正規路徑。
		"/d/longan/obj/rice_wine" : 1,
		"/d/longan/obj/zaoyu" : 1,
		"/d/longan/obj/zuixia" : 1,
		"/obj/food/manto" : 50,
		"/obj/food/fish" : 40,
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
		return notify_fail("你想問酒保些甚麼﹖（試試 ask barman about 龍安）\n");

	if( arg == "barman about 龍安"
	||  arg == "barman about 無腸酒店"
	||  arg == "barman about 酒店"
	||  arg == "barman about 米酒"
	||  arg == "barman about longan" ) {
		do_chat(({
			(: command, "say 客官是頭一回到咱龍安罷﹖這小鎮枕著水﹐巷子裡都能撐船﹐別處可少見哩。" :),
			(: command, "say 咱這龍安米酒是取溪河活水、襯荷葉封甕釀的﹐配上後堂的糟魚醉蝦﹐管教客官吃了還想再來。" :),
		}));
		return 1;
	}

	if( arg == "barman about 無腸老人"
	||  arg == "barman about 老人"
	||  arg == "barman about 無腸"
	||  arg == "barman about wuchang" ) {
		do_chat(({
			(: command, "say 客官說那位無腸老先生﹖嘿﹐他可是咱店裡的常客了﹐一日三餐都泡在酒裡﹐人都喚他『無腸老人』——說是肚裡淨是酒、沒了腸子哩。" :),
			(: command, "say 老先生一肚子的詩才﹐就是醉糊塗了。客官得空﹐自個兒去同他攀談攀談﹐興許有意想不到的造化。(ask wuchang about 煙雨詩錄)" :),
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
