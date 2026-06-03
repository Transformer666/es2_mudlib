// wonder_boots.c -- 頂級防具「六合玲瓏靴」(feet_eq)。頂裝(top-tier gear)系列。
//
// 來源(doc)：docs/02-遊戲系統與機制/05-裝備與強化.md 任務裝備列有
//   「六合玲瓏靴 (Wonder boots) — 白象寺 — 防禦能力+15、冰寒傷+10、防禦+5、冰寒防+25」。
//   本檔忠實取其名與量級，落實為頂裝靴一件。
//
// apply 鍵(僅取 driver 確實會讀的 combat 鍵，見 feature/char/combat.c 與 skill.c)：
//   doc 之效果        本檔 apply 鍵            取用處
//   ──────────       ──────────────         ──────────
//   防禦能力+15        "defense": 15           combat.c:81  apply/defense
//   防禦(護甲)+5       "armor"  : 5            combat.c:277 apply/armor
//   (身法靈便之意)      "dodge"  : 3            skill.c:123  apply/<skill> (此處 dodge)
//   (「冰寒傷/冰寒防」屬本 mudlib 版本未實作之元素 apply 鍵，從略以免無效鍵。)
//   靴類加 dodge 之慣式與 obj/armor 的既有靴(clothboot.c apply dodge)一致。
//
// feet_eq 之 setup_feet_eq() 為空殼(feature/armor/feet_eq.c)，效力全憑
//   apply_armor/feet_eq 一個 mapping，穿戴時由 equip.c 套用。
//
// 不設 unique：頂防為精良量產之物，與獨一無二之神兵性質不同(見 firescale_armor.c 同註)。

#include <armor.h>

inherit F_FEET_EQ;

void create()
{
	set_name("六合玲瓏靴", ({ "wonder boots", "boots" }));
	set_weight(1200);
	setup_feet_eq();

	if( !clonep() ) {
		set("unit", "雙");
		set("value", 38000);
		set("wear_as", "feet_eq");
		set("long",
			"這是一雙織工精絕的『六合玲瓏靴』。靴面以一種瑩白如玉的細\n"
			"絲密密織就﹐其上暗繡六合玲瓏的繁複紋路﹐隨光流轉竟似有六\n"
			"道幽微的清芒在絲縷間明滅遊走。靴底綴著數片極薄的軟玉﹐落\n"
			"地無聲﹐踏之卻穩如生根。相傳此靴出自白象寺巧手﹐穿之步履\n"
			"輕靈、進退如意﹐臨敵時身法亦因之大為玲瓏﹐既護下盤又添幾\n"
			"分閃躲騰挪之便。\n");
		set("wear_msg",
			"$N換上那雙瑩白的六合玲瓏靴﹐靴上清芒微微流轉﹐步履登時輕靈了幾分。\n");
		set("remove_msg", "$N脫下六合玲瓏靴﹐身法似乎也隨之沉滯了下來。\n");
		set("apply_armor/feet_eq", ([
			"defense" : 15,
			"armor"   : 5,
			"dodge"   : 3,
		]) );
	}

	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
