// /obj/book/wenxin_book.c -- 文心雕龍（共用悟性書）
//
// docs 02-遊戲系統與機制/06-煉丹與書本系統.md L126-129 書店清單：文心雕龍 25 兩。
// 名山書肆、儒林書坊兩家書店共用同一份 object（勿重複建檔）。
//
// 【定位】docs category「悟性書＝提升悟性 int」保守實作（F_STUDY + enlighten/int）。
//   docs 未給精確 per-book 技能映射，不臆造特定技能書效果（見 caveat）。
// 【平衡】25 兩文論名著，enlighten/int 27、required/skill/literate 15。value 2500 = 25 兩。

inherit ITEM;
inherit F_STUDY;

void create()
{
	set_name("【文心雕龍】",
		({ "wenxin", "wenxin book", "book",
		   "文心雕龍", "文心" }) );
	set_weight(900);
	if( !clonep() ) {
		set("unit", "本");
		set("value", 2500);
		set("long",
			"這是一本【文心雕龍】﹐劉勰所撰﹐體大思精﹐為文論之集\n"
			"大成者。全書五十篇﹐上溯文之樞紐﹐下論文體流變、為文\n"
			"之術﹐辭采宏富﹐義理深邃。讀書人潛心研讀﹐既能精進文\n"
			"識﹐於剖情析采、開闊悟性一道更是受用無窮。可用 study\n"
			"細細研讀。\n");
		set("required/skill", ([
			"literate" : 15,
		]));
		// content 必須存在且含至少一個「query_skill < cap」的可習技能，否則
		// feature/study.c::study_ob L43-45 在 content 閘即中止、到不了 enlighten_int、int 不升。
		// 鏡 yanyu_book/literate_book：以 literate 為可習技能，cap 與本書層級相稱、≤頂級45。
		set("content", ([
			"literate" : 32,
		]));
		set("enlighten/int", 27);   // 悟性書(docs 06 L118)，封於 min(本值,50)。
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
