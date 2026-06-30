// zhuangyuan_keeper.c -- 狀元堂掌櫃：賣書(F_VENDOR)的精明京城書商。
//
// docs 02-遊戲系統與機制/06-煉丹與書本系統.md L129 狀元堂書單：
//   大悲咒 5兩、往生經 5兩、咬文嚼字 10兩、般若 5兩、無量壽 5兩、名山文考 30兩。
// 書皆為共用悟性書 object(/obj/book/*)。merchandise 的 mapping value 是庫存數量
// (feature/npc/vendor.c)，價格取自各書 set("value")。
//
// 【runtime】純賣書、無自訂指令；init 補 add_action("do_vendor_list","list")(F_VENDOR 標準)。
//   不 replace_program。物件以英文裸 token id 認(鐵則 #6)：list/buy dabei/heart/mingshan…。

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("狀元堂掌櫃", ({ "keeper", "bookkeeper", "vendor",
		"狀元堂掌櫃", "掌櫃" }) );
	set_race("human");
	set_class("scholar");
	set_level(10);

	set("age", 45);
	set("gender", "male");
	set("long",
		"這位是狀元堂的掌櫃﹐生得一張精明面孔﹐穿一件簇新的綢緞\n"
		"長衫﹐手裡撥著算盤﹐見人三分笑。京中趕考的舉子要尋甚麼\n"
		"程墨善本﹐他無不應承得了。你可以用 list 看他賣些什麼書\n"
		"﹐用 buy 向他買書。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"狀元堂掌櫃撥著算盤﹐眼睛卻不住地往門口張望﹐招呼著進來的客人。\n",
		"狀元堂掌櫃滿面堆笑﹕公子是來尋書應考的麼﹖小店的程墨善本﹐京裡可是頭一份。\n",
		"狀元堂掌櫃壓低嗓子道﹕買幾本好書尋個清靜處 study 細讀﹐悟性開了﹐這科必中﹗\n",
		"狀元堂掌櫃笑道﹕那幾卷佛經雖只五兩﹐靜心持誦﹐於悟性也大有裨益呢。\n",
	}));
	// 狀元堂書單(docs 06 L129)。價格自各書 set("value") 讀取；此處數字為庫存。
	set("merchandise", ([
		"/obj/book/dabei_mantra" : 10,	// 大悲咒 5兩
		"/obj/book/rebirth_sutra" : 10,	// 往生經 5兩
		"/obj/book/yaowen_book" : 8,	// 咬文嚼字 10兩
		"/obj/book/heart_sutra" : 10,	// 般若波羅密多心經 5兩
		"/obj/book/longevity_sutra" : 10,	// 無量壽經 5兩
		"/obj/book/mingshan_book" : 5,	// 名山文考 30兩
	]));

	setup();
	carry_money("coin", 500);
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
}

int accept_fight(object ob)
{
	do_chat("狀元堂掌櫃慌忙縮到櫃臺後﹐連連告饒﹕光天化日、天子腳下﹐公子千萬使不得﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
