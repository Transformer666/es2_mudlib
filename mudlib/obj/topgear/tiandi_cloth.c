// tiandi_cloth.c -- 頂級防具「天地雲衫」(cloth)。頂裝(top-tier gear)系列。
//
// 來源(doc)：docs/02-遊戲系統與機制/05-裝備與強化.md L184-186「黑風寨四頭目」一節，
//   黑風寨頭目掉落物列有「天地雲衫」一件。本檔取其名落實為黑風寨頭目伏誅後掉落的頂裝
//   外衫。(docs 將四件並列於閰狂風名下﹐本副本將之分屬四頭目各一件﹐見副本設計說明；
//   此衫指派為「三頭目」翻雲手掉落。)
//
// 部位：cloth(外衫)，與 armor(身甲)分屬不同 wear slot﹐可與紫羅點翠戰甲同時穿戴。
//   F_CLOTH::setup_cloth() 為空殼(feature/armor/cloth.c)，效力全憑 apply_armor/cloth
//   一個 mapping﹔穿戴時由 equip.c 套用。鏡 obj/armor/cloth.c、d/snow/npc/obj/blue_cloth.c。
//
// apply 鍵(僅取 driver 確實會讀的 combat / skill 鍵)：
//   "defense" 守勢 (combat.c:81 apply/defense)
//   "armor"   護甲 (combat.c:277 apply/armor)——雲衫輕軟﹐護甲量級遠低於重甲﹐取小值。
//   "dodge"   閃避 (skill.c:123 apply/<skill>)——雲衫飄逸﹐主在身法靈便﹐故偏 dodge。
//   定位：一件輕軟飄逸、利於身法的上乘外衫﹐與重甲互補(重甲厚護甲、雲衫添閃避守勢)。
//
// 不設 unique：頂防為精良量產之物(與獨一無二之神兵不同)，故頭目伏誅後恒掉一件此衫。

#include <armor.h>

inherit F_CLOTH;

void create()
{
	set_name("天地雲衫", ({ "tiandi cloth", "cloud robe", "cloth" }));
	set_weight(2200);
	setup_cloth();

	if( !clonep() ) {
		set("unit", "件");
		set("value", 36000);
		set("wear_as", "cloth");
		set("long",
			"這是一件輕軟飄逸、不知以何物織就的『天地雲衫』。衫身是一\n"
			"種說不出的灰白﹐隨人舉動而流轉明滅﹐其上以銀絲暗繡著天地\n"
			"山川、雲水蒼茫的紋樣——遠望竟似一身罩著一片化不開的雲煙。\n"
			"衫料輕得幾近於無﹐握在手中似一捧流雲﹐穿在身上卻又貼合溫\n"
			"潤﹐臨敵時隨身法翻飛舒展﹐使人進退騰挪都輕靈了幾分。相傳\n"
			"此衫乃黑風寨頭目自一位雲遊高人身上劫得﹐其質非絲非錦﹐刀\n"
			"劍難以著力﹐穿之既添幾分閃躲之便﹐亦有護身禦寒之效。\n");
		set("wear_msg",
			"$N披上那件輕軟的天地雲衫﹐衫上雲水紋樣隨光流轉﹐身形登時飄逸了幾分。\n");
		set("unequip_msg", "$N脫下天地雲衫﹐那一身流雲般的飄逸之氣也隨之斂去。\n");
		set("apply_armor/cloth", ([
			"defense" : 12,
			"armor"   : 6,
			"dodge"   : 5,
		]) );
	}

	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
