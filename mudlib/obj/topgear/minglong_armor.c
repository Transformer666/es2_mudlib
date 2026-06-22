// minglong_armor.c -- 頂級防具「冥龍甲」(body armor)。頂裝(top-tier gear)系列。
//
// 來源(doc)：docs/02-遊戲系統與機制/05-裝備與強化.md L160「平陽寨主公孫一笑 → 冥龍甲、
//   金龍杖、杞庸兵書」﹐另 L215「妖塔系列」亦列冥龍甲。本檔取其「胸甲(body armor)」
//   一件落實為頂裝防具﹐定位為平陽寨主公孫一笑伏誅後可掉落的頂級護甲。
//
// 全服唯一(unique)：set("unique", 1)──冥龍甲乃公孫一笑的鎮寨之甲、簽名掉落﹐契合
//   「全服唯一」之性質(由 npc/gongsunyixiao.c::die() 走 LOOT_D->unique_drop 盤點世界
//   現存冥龍甲 clone 數﹐已有任一件則改掉普通的備援甲「玄鐵戰甲」﹐故同一件冥龍甲
//   全服任何時刻至多一件)。鏡 obj/topgear/canglang_blade.c 之 set("unique",1) 慣式。
//
// apply 鍵之取捨(僅用 driver 確實會讀的 combat 鍵﹐見 feature/char/combat.c﹐完全鏡
//   firescale_armor.c 之取捨)：
//   效果意象          本檔 apply 鍵            combat.c 取用處
//   ──────────       ──────────────         ─────────────────
//   護甲(防禦)         "armor"  : 22           combat.c:277 query_temp("apply/armor")
//                                              (受擊時真正抵減傷害的護甲值)
//   攻擊能力           "attack" : 16           combat.c:72  query_temp("apply/attack")
//   守勢(防禦能力)     "defense": 18           combat.c:81  query_temp("apply/defense")
//
//   數值取捨：本甲為頂防 body armor﹐護甲 22 略高於火鱗胸鎧(18)以彰其「龍甲」之名﹐
//   然 attack/defense 不過 firescale 之量級(16/18)﹐三項合計仍貼近既有頂防一線、不致
//   過強(勿破壞強化系統建立的戰鬥平衡)。armor.c::setup_armor() 為空殼﹐護具之效全憑
//   apply_armor/<part> 一個 mapping﹐穿戴時由 equip.c::do_equip 套用(apply())。

#include <armor.h>

inherit F_ARMOR;

void create()
{
	set_name("冥龍甲", ({ "minglong armor", "minglong jia", "armor" }));
	set_weight(13000);
	setup_armor();

	if( !clonep() ) {
		set("unit", "件");
		set("value", 60000);
		set("wear_as", "armor");
		set("unique", 1);
		set("long",
			"這是一件通體墨黑、隱透幽藍的『冥龍甲』。甲身以一片片狀如\n"
			"龍鱗的玄鐵綴成﹐每一片鱗甲都泛著一層深沉如夜的幽光﹐相疊處\n"
			"嚴絲合縫﹐宛若一條盤蜷的玄龍伏在人身。撫之沁涼徹骨﹐隱隱透\n"
			"出一股陰寒的龍威﹐傳聞乃取深淵冥龍之鱗、雜以玄鐵寒精鍛就。\n"
			"這胸甲護住前胸後背要害﹐刀劍劈砍其上但聞鏗然脆響、難傷分毫\n"
			"﹐穿在身上更隱隱助人攻守俱進——是平陽寨主公孫一笑視若性命、\n"
			"護身鎮寨的一件曠世神甲。\n");
		set("wear_msg",
			"$N將那件墨黑的冥龍甲束上身軀﹐鱗甲相疊處幽光一閃﹐隱隱透出一股陰寒的龍威。\n");
		set("unequip_msg", "$N卸下身上的冥龍甲﹐那股陰寒的龍威也隨之斂去。\n");
		set("apply_armor/armor", ([
			"armor"   : 22,
			"attack"  : 16,
			"defense" : 18,
		]) );
	}

	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
