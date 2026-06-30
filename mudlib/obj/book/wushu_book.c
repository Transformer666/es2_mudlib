// /obj/book/wushu_book.c -- 五數（共用悟性書）
//
// docs 02-遊戲系統與機制/06-煉丹與書本系統.md L126-129 書店清單：五數 22 兩。
// 名山書肆、儒林書坊兩家書店共用同一份 object（勿重複建檔）。
//
// 【定位】docs category「悟性書＝提升悟性 int」保守實作（F_STUDY + enlighten/int）。
//   docs 未給精確 per-book 技能映射，不臆造特定技能書效果（見 caveat）。
// 【平衡】22 兩較貴算學書，enlighten/int 26、required/skill/literate 12。value 2200 = 22 兩。
//   檔名 wushu_book 取「五數」拼音，與武功 manual 無涉（本書是悟性書、非武功秘笈）。

inherit ITEM;
inherit F_STUDY;

void create()
{
	set_name("【五數】",
		({ "wushu", "wushu book", "shushu", "book",
		   "五數" }) );
	set_weight(800);
	if( !clonep() ) {
		set("unit", "本");
		set("value", 2200);
		set("long",
			"這是一本【五數】﹐古來算學之要籍﹐論天地之數、方圓之\n"
			"理﹐自籌算九九以至勾股測望﹐條分縷析﹐推演入微。書中\n"
			"題例環環相扣﹐非心思縝密者不能竟其功。讀書人苦心鑽研\n"
			"﹐於推理思辨、開闊悟性一道極有助益。可用 study 研讀。\n");
		set("required/skill", ([
			"literate" : 12,
		]));
		// content 必須存在且含至少一個「query_skill < cap」的可習技能，否則
		// feature/study.c::study_ob L43-45 在 content 閘即中止、到不了 enlighten_int、int 不升。
		// 鏡 yanyu_book/literate_book：以 literate 為可習技能，cap 與本書層級相稱、≤頂級45。
		set("content", ([
			"literate" : 28,
		]));
		set("enlighten/int", 26);   // 悟性書(docs 06 L118)，封於 min(本值,50)。
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
