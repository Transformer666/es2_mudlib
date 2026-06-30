// /obj/book/rebirth_sutra.c -- 往生經（共用悟性書）
//
// docs 02-遊戲系統與機制/06-煉丹與書本系統.md L126-129 書店清單：往生經 5 兩（狀元堂）。
//
// 【定位】docs category「悟性書＝提升悟性 int」保守實作（F_STUDY + enlighten/int）。
//   docs 未給精確 per-book 技能映射，不臆造特定技能書效果（見 caveat）。
// 【平衡】5 兩低價經本，enlighten/int 20、required/skill/literate 1。value 500 = 5 兩。

inherit ITEM;
inherit F_STUDY;

void create()
{
	set_name("【往生經】",
		({ "rebirth", "rebirth sutra", "sutra", "book",
		   "往生經", "往生" }) );
	set_weight(600);
	if( !clonep() ) {
		set("unit", "卷");
		set("value", 500);
		set("long",
			"這是一卷【往生經】﹐全名拔一切業障根本得生淨土陀羅尼\n"
			"﹐俗稱往生咒。經文短小﹐專為超度亡魂、往生淨土而設。\n"
			"持誦之際﹐令人念及生死無常﹐心境澄明﹐於體察萬物、開\n"
			"闊悟性一道頗有所得。可用 study 細細研讀。\n");
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
