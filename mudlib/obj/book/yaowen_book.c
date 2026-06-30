// /obj/book/yaowen_book.c -- 咬文嚼字（共用悟性書）
//
// docs 02-遊戲系統與機制/06-煉丹與書本系統.md L126-129 書店清單：咬文嚼字 10 兩（狀元堂）。
//
// 【定位】docs category「悟性書＝提升悟性 int」保守實作（F_STUDY + enlighten/int）。
//   docs 未給精確 per-book 技能映射，不臆造特定技能書效果（見 caveat）。
// 【平衡】10 兩中價文書，enlighten/int 24、required/skill/literate 5。value 1000 = 10 兩。

inherit ITEM;
inherit F_STUDY;

void create()
{
	set_name("【咬文嚼字】",
		({ "yaowen", "yaowen book", "book",
		   "咬文嚼字" }) );
	set_weight(700);
	if( !clonep() ) {
		set("unit", "本");
		set("value", 1000);
		set("long",
			"這是一本【咬文嚼字】﹐專論遣詞用字、辨析音義之學。書\n"
			"中一字一句細加推敲﹐辨同異、正訛謬﹐讀來令人於字裡行\n"
			"間別有體會。讀書人案頭備此一本﹐推敲琢磨之間﹐文識與\n"
			"悟性俱有長進。可用 study 細細研讀。\n");
		set("required/skill", ([
			"literate" : 5,
		]));
		// content 必須存在且含至少一個「query_skill < cap」的可習技能，否則
		// feature/study.c::study_ob L43-45 在 content 閘即中止、到不了 enlighten_int、int 不升。
		// 鏡 yanyu_book/literate_book：以 literate 為可習技能，cap 與本書層級相稱、≤頂級45。
		set("content", ([
			"literate" : 20,
		]));
		set("enlighten/int", 24);   // 悟性書(docs 06 L118)，封於 min(本值,50)。
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
