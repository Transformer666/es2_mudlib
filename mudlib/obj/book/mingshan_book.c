// /obj/book/mingshan_book.c -- 名山文考（共用悟性書）
//
// docs 02-遊戲系統與機制/06-煉丹與書本系統.md L126-129 書店清單：名山文考 30 兩。
// 名山書肆、儒林書坊、狀元堂【三家】書店共用同一份 object（勿重複建檔）。
//
// 【定位】docs category「悟性書＝提升悟性 int」保守實作（F_STUDY + enlighten/int）。
//   docs 未給精確 per-book 技能映射，不臆造特定技能書效果（見 caveat）。
// 【平衡】30 兩高價考據書，enlighten/int 28、required/skill/literate 18。value 3000 = 30 兩。

inherit ITEM;
inherit F_STUDY;

void create()
{
	set_name("【名山文考】",
		({ "mingshan", "mingshan book", "book",
		   "名山文考", "名山" }) );
	set_weight(1000);
	if( !clonep() ) {
		set("unit", "本");
		set("value", 3000);
		set("long",
			"這是一本【名山文考】﹐遍考天下名山勝跡、碑碣文獻而成\n"
			"的一部考據鉅著。書中徵引浩繁﹐自金石碑刻以至方志野史\n"
			"﹐辨偽存真﹐考訂精審﹐讀來令人神遊宇內、學問大進。讀\n"
			"書人窮年皓首於斯﹐文識與悟性俱臻上乘。可用 study 研讀。\n");
		set("required/skill", ([
			"literate" : 18,
		]));
		// content 必須存在且含至少一個「query_skill < cap」的可習技能，否則
		// feature/study.c::study_ob L43-45 在 content 閘即中止、到不了 enlighten_int、int 不升。
		// 鏡 yanyu_book/literate_book：以 literate 為可習技能，cap 與本書層級相稱、≤頂級45。
		set("content", ([
			"literate" : 35,
		]));
		set("enlighten/int", 28);   // 悟性書(docs 06 L118)，封於 min(本值,50)。
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
