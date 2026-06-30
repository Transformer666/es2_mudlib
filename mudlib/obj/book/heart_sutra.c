// /obj/book/heart_sutra.c -- 般若波羅密多心經（共用悟性書）
//
// docs 02-遊戲系統與機制/06-煉丹與書本系統.md L126-129 書店清單：般若波羅密多心經 5 兩。
// 名山書肆、狀元堂兩家書店共用同一份 object（勿重複建檔）。
//
// 【定位】docs 06 L116-118 書本三類，本書按 docs category「悟性書＝提升悟性 int」保守實作
//   （F_STUDY + enlighten/int，鏡 feature/study.c::enlighten_int 機制）。docs 只給書名+價、
//   未給精確 per-book 技能映射，故不臆造「學特定武功招式」之技能書效果（見 caveat）。
// 【平衡】5 兩低價佛經，enlighten/int 取低段 20（高於常人初始悟性、留成長空間，遠低於
//   ATTRVAL_MAX=50 硬上限，study.c 雙重夾值，絕不無限增長）。required/skill/literate 1
//   （低門檻，初窺文墨者亦可誦讀）。value 500 = 5 兩（vendor price_string 以 value/100 計兩）。

inherit ITEM;
inherit F_STUDY;

void create()
{
	set_name("【般若波羅密多心經】",
		({ "heart", "sutra", "heart sutra", "book",
		   "般若波羅密多心經", "心經", "般若" }) );
	set_weight(600);
	if( !clonep() ) {
		set("unit", "卷");
		set("value", 500);
		set("long",
			"這是一卷坊間刻印的【般若波羅密多心經】﹐短短二百餘字﹐\n"
			"卻是般若部經文的精要。經中「色即是空、空即是色」之語﹐\n"
			"道盡諸法空相之理。靜心持誦再三﹐於體察世情、開闊悟性一\n"
			"道頗有助益。可用 study 細細研讀。\n");
		set("required/skill", ([
			"literate" : 1,
		]));
		// content 必須存在且含至少一個「query_skill < cap」的可習技能，否則
		// feature/study.c::study_ob L43-45 在 content 閘即中止研讀、永遠到不了
		// enlighten_int(L137)——int 不會升。鏡 yanyu_book/literate_book 範式：
		// 以 literate 為可習技能(study 核心進度技能)，cap 與本書門檻/層級相稱、≤頂級書45。
		set("content", ([
			"literate" : 15,
		]));
		set("enlighten/int", 20);   // 悟性書(docs 06 L118)，遞減機率每拍至多 +1，封於 min(本值,50)。
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
