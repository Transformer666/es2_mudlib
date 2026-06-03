// firescale_armor.c -- 頂級防具「火鱗胸鎧」(body armor)。頂裝(top-tier gear)系列。
//
// 來源(doc)：docs/02-遊戲系統與機制/05-裝備與強化.md 列有「火鱗套組」(柳東蘆掉)
//   ——「攻擊能力+18、火焰防+25、防禦+15、內功+10」﹐並於套裝來源列出柳東蘆掉
//   「火鱗衣/胸鎧/靴/盔/手套/腰帶/脛甲」一整套。本檔取其中之「胸鎧」一件落實為
//   頂裝防具。
//
// apply 鍵之取捨(僅用 driver 確實會讀的 combat 鍵，見 feature/char/combat.c)：
//   doc 之效果        本檔 apply 鍵            combat.c 取用處
//   ──────────       ──────────────         ─────────────────
//   防禦(護甲)+15      "armor"  : 18           combat.c:277 query_temp("apply/armor")
//                                              (受擊時真正抵減傷害的護甲值)
//   攻擊能力+18        "attack" : 18           combat.c:72  query_temp("apply/attack")
//   防禦能力(守勢)     "defense": 15           combat.c:81  query_temp("apply/defense")
//   (「火焰防/內功」屬本 mudlib 版本未實作之元素/內功 apply 鍵，從略以免無效鍵；
//    僅保留確有作用的 armor/attack/defense 三項，數值貼合 doc 的火鱗套量級。)
//
//   armor.c 之 setup_armor() 為空殼(見 feature/armor/armor.c)，護具之效全憑
//   apply_armor/<part> 一個 mapping；穿戴時由 equip.c::do_equip 套用(apply())。
//   identify(cmds/std/identify.c)會以「護具特性」列出此 mapping。
//
// 此為「套組之首件」，刻意「不」設 unique——頂防屬可量產之精良甲冑(doc 火鱗為一
//   整套、可拼湊)，與獨一無二之神兵性質不同；亦留待日後補齊全套(靴/盔/手套…)時
//   做套裝加成(set bonus)之伏筆(此為 OPEN DESIGN，見報告)。

#include <armor.h>

inherit F_ARMOR;

void create()
{
	set_name("火鱗胸鎧", ({ "firescale armor", "armor" }));
	set_weight(11000);
	setup_armor();

	if( !clonep() ) {
		set("unit", "件");
		set("value", 45000);
		set("wear_as", "armor");
		set("long",
			"這是一件以赤紅鱗甲層層綴成的『火鱗胸鎧』。每一片鱗甲都泛\n"
			"著一種熔金般的暗紅光澤﹐邊緣鍍著一線焦黃﹐相疊處嚴絲合縫\n"
			"如真龍之鱗﹐撫之竟有微微的溫熱自掌下傳來﹐傳聞乃取火屬異\n"
			"獸之鱗、雜以精鐵鍛就。這胸鎧護住前胸後背要害﹐防護周密而\n"
			"不失輕便﹐既能卸去刀劍劈砍之力﹐穿在身上更隱隱透出一股逼\n"
			"人的火屬氣勁﹐助人攻守俱進——是火鱗一套頂級甲冑中護住周身\n"
			"的主件。\n");
		set("wear_msg",
			"$N將那件暗紅的火鱗胸鎧束上身軀﹐鱗甲相疊處微微一亮﹐隱隱透出一股逼人的熱氣。\n");
		set("unequip_msg", "$N卸下身上的火鱗胸鎧﹐那股逼人的熱氣也隨之斂去。\n");
		set("apply_armor/armor", ([
			"armor"   : 18,
			"attack"  : 18,
			"defense" : 15,
		]) );
	}

	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
