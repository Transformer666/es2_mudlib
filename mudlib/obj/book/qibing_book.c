// /obj/book/qibing_book.c -- 奇兵摘要（共用悟性書）
//
// docs 02-遊戲系統與機制/06-煉丹與書本系統.md L126-129 書店清單：奇兵摘要 50 兩（名山書肆）。
//
// 【定位】docs category「悟性書＝提升悟性 int」保守實作（F_STUDY + enlighten/int）。
//   docs 未給精確 per-book 技能映射，不臆造特定技能書效果（見 caveat）——
//   雖書名涉兵法，docs 未明言其「學特定兵法/武功技能」之效，故仍按悟性書保守解讀；
//   日後若設計者定其為「兵法 strategy 技能書」，可另加 content（["strategy":N]）。
// 【平衡】50 兩最貴兵書（書店清單中最高價），enlighten/int 30（接近 yanyu_book 頂級 32、
//   仍遠低於 ATTRVAL_MAX=50），required/skill/literate 25。value 5000 = 50 兩。

inherit ITEM;
inherit F_STUDY;

void create()
{
	set_name("【奇兵摘要】",
		({ "qibing", "qibing book", "book",
		   "奇兵摘要", "奇兵" }) );
	set_weight(800);
	if( !clonep() ) {
		set("unit", "本");
		set("value", 5000);
		set("long",
			"這是一本【奇兵摘要】﹐輯錄歷代用兵出奇制勝的方略而成\n"
			"的一部兵書。書中所論﹐自虛實奇正、因敵制變以至山川地\n"
			"利、間諜火攻﹐無不洞中竅要﹐字字珠璣。此書世所罕見﹐\n"
			"得之者珍若拱璧。沉潛研讀﹐推演方略之間﹐心思益發縝密\n"
			"﹐悟性大開。可用 study 細細研讀。\n");
		set("required/skill", ([
			"literate" : 25,
		]));
		// content 必須存在且含至少一個「query_skill < cap」的可習技能，否則
		// feature/study.c::study_ob L43-45 在 content 閘即中止、到不了 enlighten_int、int 不升。
		// 鏡 yanyu_book/literate_book：以 literate 為可習技能，cap 與本書層級相稱、≤頂級45。
		set("content", ([
			"literate" : 40,
		]));
		set("enlighten/int", 30);   // 悟性書(docs 06 L118)，封於 min(本值,50)。
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
