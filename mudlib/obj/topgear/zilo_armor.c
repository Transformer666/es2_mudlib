// zilo_armor.c -- 頂級防具「紫羅點翠戰甲」(body armor)。頂裝(top-tier gear)系列。
//
// 來源(doc)：docs/02-遊戲系統與機制/05-裝備與強化.md L184-186「黑風寨四頭目」一節，
//   黑風寨頭目掉落物列有「紫羅點翠戰甲」一件。本檔取其名落實為黑風寨頭目伏誅後掉落
//   的頂裝身甲。(docs 將四件並列於閰狂風名下﹐本副本將之分屬四頭目各一件﹐見副本設計
//   說明；此甲指派為「二頭目」鐵臂熊掉落。)
//
// apply 鍵之取捨(僅用 driver 確實會讀的 combat 鍵，鏡 firescale_armor.c)：
//   "armor"   受擊時真正抵減傷害的護甲值 (combat.c:277 query_temp("apply/armor"))
//   "attack"  攻擊能力 (combat.c:72 apply/attack)
//   "defense" 守勢 (combat.c:81 apply/defense)
//   數值貼合頂防量級﹐略高於火鱗胸鎧(armor18/attack18/defense15)——本甲為「點翠」紫羅織就、
//   鑲嵌甲片之重甲﹐護甲偏厚而攻勢稍遜﹐定位略偏防禦。
//
//   armor.c::setup_armor() 為空殼(feature/armor/armor.c)，護具之效全憑 apply_armor/<part>
//   一個 mapping﹔穿戴時由 equip.c::do_equip 套用(apply())。identify 會以「護具特性」列之。
//
// 此為頂防身甲，刻意「不」設 unique——頂防屬可量產之精良甲冑(與獨一無二之神兵不同)，
//   故黑風寨頭目伏誅後恒掉一件此甲(非全服唯一)，使每次擊殺皆有像樣身甲可得。

#include <armor.h>

inherit F_ARMOR;

void create()
{
	set_name("紫羅點翠戰甲", ({ "zilo armor", "armor" }));
	set_weight(12000);
	setup_armor();

	if( !clonep() ) {
		set("unit", "件");
		set("value", 52000);
		set("wear_as", "armor");
		set("long",
			"這是一件以名貴紫羅綢層層綴成、再以點翠之法鑲嵌甲片的『紫\n"
			"羅點翠戰甲』。羅面是一種沉鬱華貴的暗紫﹐隨光流轉竟泛著幽\n"
			"微的寶光﹐其上以翠鳥之羽點綴成纏枝的雲紋﹐青翠欲滴﹐華美\n"
			"中自有一股逼人的煞氣。羅內密綴著一片片打磨光潤的精鋼甲\n"
			"片﹐相疊處嚴絲合縫﹐護住前胸後背要害﹐既卸得去刀劍劈砍之\n"
			"力﹐又不失輕便。相傳此甲乃黑風寨頭目自一支劫掠的商隊裡奪\n"
			"來﹐本是某位王侯的禦戰之服﹐落入綠林﹐遂成了寨中頭目壓陣\n"
			"的鎮身重甲。\n");
		set("wear_msg",
			"$N將那件暗紫的紫羅點翠戰甲束上身軀﹐點翠的雲紋隨光流轉﹐華美中隱透一股煞氣。\n");
		set("unequip_msg", "$N卸下身上的紫羅點翠戰甲﹐那身華貴的煞氣也隨之斂去。\n");
		set("apply_armor/armor", ([
			"armor"   : 22,
			"attack"  : 12,
			"defense" : 18,
		]) );
	}

	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
