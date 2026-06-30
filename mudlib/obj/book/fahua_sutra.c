// /obj/book/fahua_sutra.c -- 法華經（共用悟性書）
//
// docs 02-遊戲系統與機制/06-煉丹與書本系統.md L128,130 書店清單：
//   寶蓮寺、白象寺客房 2F 皆售「法華經」5 兩。兩店共用同一份 object（勿重複建檔）。
//
// 【定位】docs 06 L116-118 書本三類，本書按 docs category「悟性書＝提升悟性 int」保守實作
//   （F_STUDY + enlighten/int，鏡 heart_sutra/longevity_sutra 範式）。docs 只給書名+價、
//   未給精確 per-book 技能映射，故不臆造「學特定武功招式」之技能書效果（見 caveat）。
// 【平衡】5 兩低價佛經，enlighten/int 20、required/skill/literate 1。value 500 = 5 兩。

inherit ITEM;
inherit F_STUDY;

void create()
{
	set_name("【法華經】",
		({ "fahua", "fahua sutra", "sutra", "book",
		   "法華經", "法華", "妙法蓮華經" }) );
	set_weight(700);
	if( !clonep() ) {
		set("unit", "卷");
		set("value", 500);
		set("long",
			"這是一卷【妙法蓮華經】﹐略稱法華經﹐乃大乘佛教群經之\n"
			"王。經中以蓮華為喻﹐宣說諸佛出世唯為令眾生開示悟入佛\n"
			"之知見。卷帙雖繁﹐文辭瑰麗﹐譬喻層出﹐靜心諷誦再三﹐\n"
			"於體察世情、開闊悟性一道大有裨益。可用 study 細細研讀。\n");
		set("required/skill", ([
			"literate" : 1,
		]));
		// content 必須存在且含至少一個「query_skill < cap」的可習技能，否則
		// feature/study.c::study_ob L43-45 在 content 閘即中止、到不了 enlighten_int、int 不升。
		// 鏡 heart_sutra/yanyu_book：以 literate 為可習技能，cap 與本書層級相稱、≤頂級45。
		set("content", ([
			"literate" : 15,
		]));
		set("enlighten/int", 20);   // 悟性書(docs 06 L118)，封於 min(本值,50)。
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
