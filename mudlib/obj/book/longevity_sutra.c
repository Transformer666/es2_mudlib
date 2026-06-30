// /obj/book/longevity_sutra.c -- 無量壽經（共用悟性書）
//
// docs 02-遊戲系統與機制/06-煉丹與書本系統.md L126-129 書店清單：無量壽經 5 兩。
// 名山書肆、狀元堂兩家書店共用同一份 object（勿重複建檔）。
//
// 【定位】docs category「悟性書＝提升悟性 int」保守實作（F_STUDY + enlighten/int）。
//   docs 未給精確 per-book 技能映射，不臆造特定技能書效果（見 caveat）。
// 【平衡】5 兩低價佛經，enlighten/int 20、required/skill/literate 1。value 500 = 5 兩。

inherit ITEM;
inherit F_STUDY;

void create()
{
	set_name("【無量壽經】",
		({ "longevity", "longevity sutra", "sutra", "book",
		   "無量壽經", "無量壽" }) );
	set_weight(700);
	if( !clonep() ) {
		set("unit", "卷");
		set("value", 500);
		set("long",
			"這是一卷【無量壽經】﹐淨土三經之一﹐宣說西方極樂淨土\n"
			"莊嚴之相與無量壽佛宏願。卷帙雖長﹐文辭卻平易曉暢﹐讀\n"
			"來令人胸懷澄澈、雜念漸消。靜心諷誦﹐於開闊悟性一道頗\n"
			"有裨益。可用 study 細細研讀。\n");
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
