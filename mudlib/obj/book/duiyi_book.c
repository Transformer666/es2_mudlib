// /obj/book/duiyi_book.c -- 黃山對弈錄（共用悟性書 / 棋譜）
//
// docs 02-遊戲系統與機制/06-煉丹與書本系統.md L130 白象寺客房 2F 書店清單：
//   「黃山對弈錄 30文」。
//
// 【定位】docs 06 L116-118 書本三類。docs 未給此書效果、只給書名+價﹐故按 docs category
//   「悟性書＝提升悟性 int」保守實作（F_STUDY + enlighten/int，鏡 heart_sutra 範式）。
//   棋譜以推演棋局磨礪心智﹐歸入悟性書合理而不臆造特定技能書效果（見 caveat）。
// 【價】docs 字面標「30文」﹐照取 value 30（文錢，price_string 以 value 計：30文）。
//   注：同書於名山書肆等他處未列﹐他店書多以「兩」計﹐此處 30文 疑為 docs 筆誤；
//   本批一律照 docs 字面取值、不擅改（見 caveat）。
// 【平衡】棋譜屬精研之物﹐required/literate 8（須略通文墨方能看懂棋訣）、
//   enlighten/int 22（略高於佛經 20、仍遠低於 ATTRVAL_MAX=50）、content/literate cap 18。

inherit ITEM;
inherit F_STUDY;

void create()
{
	set_name("【黃山對弈錄】",
		({ "duiyi", "duiyi book", "book",
		   "黃山對弈錄", "對弈錄", "棋譜" }) );
	set_weight(500);
	if( !clonep() ) {
		set("unit", "卷");
		set("value", 30);
		set("long",
			"這是一卷【黃山對弈錄】﹐錄的是昔年黃山棋會上幾局名手\n"
			"對弈的棋譜。卷中黑白縱橫﹐布局、攻殺、收官一一注明﹐\n"
			"間或附以妙手評點。手談一道講究算路綿密、籌謀全局﹐照\n"
			"著棋譜逐手推演再三﹐於磨礪心智、開闊悟性頗有所助。可\n"
			"用 study 細細研讀。\n");
		set("required/skill", ([
			"literate" : 8,
		]));
		// content 必須存在且含至少一個「query_skill < cap」的可習技能，否則
		// feature/study.c::study_ob L43-45 在 content 閘即中止、永遠到不了 enlighten_int。
		// 以 literate 為可習技能，cap 與本書門檻相稱（高於門檻 8、≤頂級45）。
		set("content", ([
			"literate" : 18,
		]));
		set("enlighten/int", 22);   // 悟性書(docs 06 L118)，封於 min(本值,50)。
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
