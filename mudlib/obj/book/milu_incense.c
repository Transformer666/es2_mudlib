// /obj/book/milu_incense.c -- 迷羅香（共用薰香道具）
//
// docs 02-遊戲系統與機制/06-煉丹與書本系統.md L128,130 書店清單：
//   寶蓮寺、白象寺客房 2F 皆售「迷羅香 15兩」。兩店共用同一份 object。
//
// 【定位／保守取捨】docs 另處(法術系統)把「迷羅香」列為一種「控制法術」﹐需有施法/
//   狀態效果引擎(effect engine)方能實作——該引擎為 speculative、本批不臆造。故本批
//   只把迷羅香做成「可在書店買到的薰香道具」(純 ITEM、無 study/無施法效果、純佔位)﹐
//   既補足 docs 書店清單品項、又不無中生有出一套法術機制或假的悟性效果（見 caveat）。
//   待日後法術/狀態效果引擎落地﹐再於此檔補上其控制法術本意。
// 【價】15兩 = value 1500（price_string 以 value/100 計兩）。放在 obj/book/ 下與同店書共置。

inherit ITEM;

void create()
{
	set_name("【迷羅香】",
		({ "milu", "milu incense", "incense",
		   "迷羅香", "迷羅" }) );
	set_weight(300);
	if( !clonep() ) {
		set("unit", "束");
		set("value", 1500);
		set("long",
			"這是一束以番邦異草和秘製香料合成的【迷羅香】﹐通體呈\n"
			"暗赭之色﹐隱隱透著一股甜膩的異香。相傳此香點燃之後煙\n"
			"氣裊裊﹐能擾人心神、教人神思昏沉﹐故為江湖人物所重。\n"
			"此刻它只是一束尋常薰香﹐尚未顯出甚麼神異之處。\n");
	}
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
