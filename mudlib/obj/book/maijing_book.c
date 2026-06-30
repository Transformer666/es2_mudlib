// /obj/book/maijing_book.c -- 脈經注（共用悟性書）
//
// docs 02-遊戲系統與機制/06-煉丹與書本系統.md L126-129 書店清單：脈經注 18 兩。
// 名山書肆、儒林書坊兩家書店共用同一份 object（勿重複建檔）。
//
// 【定位】docs category「悟性書＝提升悟性 int」保守實作（F_STUDY + enlighten/int）。
//   docs 未給精確 per-book 技能映射，不臆造特定技能書效果（見 caveat）——
//   雖書名涉醫理，docs 未明言其「學醫術技能」之效，故仍按悟性書保守解讀。
// 【平衡】18 兩較貴經注，enlighten/int 25、required/skill/literate 10。value 1800 = 18 兩。

inherit ITEM;
inherit F_STUDY;

void create()
{
	set_name("【脈經注】",
		({ "maijing", "maijing book", "book",
		   "脈經注", "脈經" }) );
	set_weight(900);
	if( !clonep() ) {
		set("unit", "本");
		set("value", 1800);
		set("long",
			"這是一本【脈經注】﹐前賢就王叔和《脈經》逐句箋注而成\n"
			"﹐詳辨二十八脈之象、寸關尺三部之候。書中圖文並茂﹐脈\n"
			"理精微﹐非有相當文識難以盡解。讀書人沉潛其中﹐反覆推\n"
			"求醫理脈象之妙﹐於悟性一道大有長進。可用 study 研讀。\n");
		set("required/skill", ([
			"literate" : 10,
		]));
		// content 必須存在且含至少一個「query_skill < cap」的可習技能，否則
		// feature/study.c::study_ob L43-45 在 content 閘即中止、到不了 enlighten_int、int 不升。
		// 鏡 yanyu_book/literate_book：以 literate 為可習技能，cap 與本書層級相稱、≤頂級45。
		set("content", ([
			"literate" : 25,
		]));
		set("enlighten/int", 25);   // 悟性書(docs 06 L118)，封於 min(本值,50)。
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
