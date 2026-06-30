// d/baixiang/npc/innkeeper.c -- 白象寺客房二樓知客僧：照看客房書籍乾糧流通(F_VENDOR)。
//
// docs 02-遊戲系統與機制/06-煉丹與書本系統.md L130 白象寺客房 2F 書單：
//   黃山對弈錄 30文、迷羅香 15兩、法華經/佛名經 5兩、饅頭 10文、灰草菇 90文、小山豬果 10兩。
// 書/香為共用 object(/obj/book/*)；乾糧傷藥複用既有 /obj/food、/obj/medication 物件
//   (饅頭=/obj/food/manto、灰草菇=/obj/medication/gray_mushroom、小山豬果=/obj/medication/boar_berry)。
// merchandise 的 mapping value 是「庫存數量」(feature/npc/vendor.c)，價格取自各物件 set("value")。
//   食物為 COMBINED_ITEM，value=(:render_value:)=base_value*amount：manto 10文、gray_mushroom
//   90文、boar_berry 2000文=20兩。docs 標小山豬果「10兩」、既有物件 base_value 2000=20兩；
//   本批複用既有物件、不擅改其數值(見 caveat)。
//
// 【runtime】純流通、無自訂指令；init 補 add_action("do_vendor_list","list")(F_VENDOR 標準)。
//   不 replace_program。物件以英文裸 token id 認(鐵則 #6)：list/buy duiyi/manto/mushroom…。

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("知客僧", ({ "innkeeper", "keeper", "monk", "vendor",
		"知客僧", "知客" }) );
	set("nickname", "客房知客僧");
	set_race("human");
	set_class("bonze");
	set_level(10);

	set("age", 40);
	set("gender", "male");
	set("long",
		"這位是白象寺管客房的知客僧﹐生得敦實和氣﹐一襲灰布僧袍\n"
		"乾乾淨淨。他守著客房二樓的木格架﹐替投宿的香客張羅經卷\n"
		"棋譜、線香乾糧諸般用度﹐辦事妥帖周到。你可以用 list 看他\n"
		"備了些什麼﹐用 buy 向他請些回去。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"知客僧雙手合十道﹕阿彌陀佛﹐施主遠來辛苦﹐先歇歇腳罷。\n",
		"知客僧招呼道﹕經卷棋譜、線香乾糧﹐施主路上用得著的﹐小僧這兒都備著些。\n",
		"知客僧道﹕趕路的施主多帶幾個饅頭、些傷藥傍身﹐山高路遠﹐莫餓著傷著了。\n",
		"知客僧拈起那卷黃山對弈錄笑道﹕這棋譜是位掛單的居士留下的﹐難得有人問津哩。\n",
	}));
	// 白象寺客房 2F 書單(docs 06 L130)。價格自各物件 set("value") 讀取；此處數字為庫存。
	set("merchandise", ([
		"/obj/book/duiyi_book" : 5,				// 黃山對弈錄 30文(棋譜悟性書)
		"/obj/book/milu_incense" : 5,			// 迷羅香 15兩(薰香道具)
		"/obj/book/fahua_sutra" : 10,			// 法華經 5兩
		"/obj/book/foming_sutra" : 10,			// 佛名經 5兩
		"/obj/food/manto" : 20,					// 饅頭 10文(既有 food，base_value 10)
		"/obj/medication/gray_mushroom" : 15,	// 灰草菇 90文(既有 medication，base_value 90)
		"/obj/medication/boar_berry" : 10,		// 小山豬果 既有 base_value 2000=20兩(docs 標10兩，複用不改)
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
	do_chat("知客僧連忙合十道﹕佛門清淨之地﹐施主萬莫動粗﹗阿彌陀佛。\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
