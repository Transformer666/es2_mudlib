// mingshan_keeper.c -- 名山書肆掌櫃：賣書(F_VENDOR)的飽學老書商。
//
// docs 02-遊戲系統與機制/06-煉丹與書本系統.md L126 名山書肆書單：
//   脈經注 18兩、名山文考 30兩、奇兵摘要 50兩、五數 22兩、文心雕龍 25兩、
//   般若波羅密多心經 5兩、無量壽經 5兩。
// 書皆為共用悟性書 object(/obj/book/*)，三家書店共用同物件。
// merchandise 的 mapping value 是「庫存數量」(feature/npc/vendor.c)，價格取自各書 set("value")。
//
// 【runtime】本 NPC 純賣書、無自訂指令；init 補 add_action("do_vendor_list","list")(F_VENDOR 標準)。
//   不 replace_program(NPC 本就不該)。物件以英文裸 token id 認(鐵則 #6)：list/buy heart/maijing…。

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("書肆掌櫃", ({ "keeper", "bookkeeper", "vendor",
		"書肆掌櫃", "掌櫃" }) );
	set_race("human");
	set_class("scholar");
	set_level(10);

	set("age", 62);
	set("gender", "male");
	set("long",
		"這位是名山書肆的老掌櫃﹐面目清癯﹐戴一副舊水晶眼鏡﹐一\n"
		"襲半舊的儒衫漿洗得乾乾淨淨。他自幼浸淫書冊﹐學問淵博﹐\n"
		"店裡哪一本書放在哪一格都記得分毫不差。你可以用 list 看\n"
		"他賣些什麼書﹐用 buy 向他買書。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"書肆掌櫃推了推眼鏡﹐就著天光細細校讀手裡的書冊。\n",
		"書肆掌櫃和氣地說道﹕客官是來尋書的麼﹖小店經、史、子、集、佛經算書都還齊備。\n",
		"書肆掌櫃道﹕讀書一道﹐貴在悟性。買幾本好書尋個清靜處 study 細讀﹐悟性自會日進。\n",
		"書肆掌櫃捻鬚道﹕那卷奇兵摘要乃世所罕見的兵書﹐索價雖高﹐卻是物有所值。\n",
	}));
	// 名山書肆書單(docs 06 L126)。價格自各書 set("value") 讀取；此處數字為庫存。
	set("merchandise", ([
		"/obj/book/maijing_book" : 5,	// 脈經注 18兩
		"/obj/book/mingshan_book" : 5,	// 名山文考 30兩
		"/obj/book/qibing_book" : 2,	// 奇兵摘要 50兩(罕見、庫存少)
		"/obj/book/wushu_book" : 5,	// 五數 22兩
		"/obj/book/wenxin_book" : 5,	// 文心雕龍 25兩
		"/obj/book/heart_sutra" : 10,	// 般若波羅密多心經 5兩
		"/obj/book/longevity_sutra" : 10,	// 無量壽經 5兩
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
	do_chat("書肆掌櫃連忙護住書冊﹐連聲道﹕書香之地﹐動什麼粗﹖客官息怒﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
