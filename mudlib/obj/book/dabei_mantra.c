// /obj/book/dabei_mantra.c -- 大悲咒（共用悟性書）
//
// docs 02-遊戲系統與機制/06-煉丹與書本系統.md L126-129 書店清單：大悲咒 5 兩（狀元堂）。
//
// 【定位】docs category「悟性書＝提升悟性 int」保守實作（F_STUDY + enlighten/int）。
//   docs 未給精確 per-book 技能映射，不臆造特定技能書效果（見 caveat）。
// 【平衡】5 兩低價咒本，enlighten/int 20、required/skill/literate 1。value 500 = 5 兩。

inherit ITEM;
inherit F_STUDY;

void create()
{
	set_name("【大悲咒】",
		({ "dabei", "dabei mantra", "mantra", "book",
		   "大悲咒", "大悲" }) );
	set_weight(500);
	if( !clonep() ) {
		set("unit", "卷");
		set("value", 500);
		set("long",
			"這是一卷【大悲咒】﹐又名千手千眼觀世音菩薩廣大圓滿無\n"
			"礙大悲心陀羅尼。全咒八十四句﹐音節鏗鏘﹐相傳虔心持誦\n"
			"能消災解厄。一字一句細細參詳﹐心神專注之間﹐於悟性一\n"
			"道亦有開發。可用 study 細細研讀。\n");
		set("required/skill", ([
			"literate" : 1,
		]));
		// content 必須存在且含至少一個「query_skill < cap」的可習技能，否則
		// feature/study.c::study_ob L43-45 在 content 閘即中止、到不了 enlighten_int、int 不升。
		// 鏡 yanyu_book/literate_book：以 literate 為可習技能，cap 與本書層級相稱、≤頂級45。
		set("content", ([
			"literate" : 15,
		]));
		set("enlighten/int", 20);   // 悟性書(docs 06 L118)，封於 min(本值,50)。
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
