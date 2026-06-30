// xushimu.c -- 儒林書坊徐師母：賣書(F_VENDOR)的軍眷書坊主人。
//
// docs 02-遊戲系統與機制/06-煉丹與書本系統.md L127 儒林書坊（徐師母）書單：
//   脈經注 18兩、名山文考 30兩、五數 22兩、文心雕龍 25兩。
// 書皆為共用悟性書 object(/obj/book/*)。merchandise 的 mapping value 是庫存數量
// (feature/npc/vendor.c)，價格取自各書 set("value")。
//
// 【runtime】純賣書、無自訂指令；init 補 add_action("do_vendor_list","list")(F_VENDOR 標準)。
//   不 replace_program。物件以英文裸 token id 認(鐵則 #6)：list/buy maijing/mingshan/wushu/wenxin。

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("徐師母", ({ "xushimu", "shimu", "vendor",
		"徐師母", "師母" }) );
	set_race("human");
	set_class("scholar");
	set_level(8);

	set("age", 48);
	set("gender", "female");
	set("long",
		"這位徐師母是軍中一位老教習的渾家﹐生得溫婉端莊﹐一身洗\n"
		"得發白的布衣裙﹐鬢邊簪著一枝素銀簪子。她隨夫駐在軍營邊\n"
		"上﹐閒來便開了這爿小書坊﹐賣些經史算書貼補家用﹐待人很\n"
		"是和氣。你可以用 list 看她賣些什麼書﹐用 buy 向她買書。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"徐師母低頭做著針黹﹐聞得有人進來﹐和氣地抬頭招呼。\n",
		"徐師母輕聲道﹕這位客官是來尋書的麼﹖小店書雖不多﹐倒都是正經的好書。\n",
		"徐師母歎道﹕我家那口子常說﹐當兵的也該識幾個字、明些事理﹐這書坊便是這麼開起來的。\n",
		"徐師母道﹕買了書﹐尋個清靜處 study 細讀﹐悟性開了﹐做甚麼都順當些。\n",
	}));
	// 儒林書坊書單(docs 06 L127)。價格自各書 set("value") 讀取；此處數字為庫存。
	set("merchandise", ([
		"/obj/book/maijing_book" : 5,	// 脈經注 18兩
		"/obj/book/mingshan_book" : 5,	// 名山文考 30兩
		"/obj/book/wushu_book" : 5,	// 五數 22兩
		"/obj/book/wenxin_book" : 5,	// 文心雕龍 25兩
	]));

	setup();
	carry_money("coin", 300);
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
}

int accept_fight(object ob)
{
	do_chat("徐師母嚇得花容失色﹐護住書冊連聲道﹕這位客官莫要動粗﹐有話好說﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
