// grayhare.c -- 灰兔，野獸山林邊緣最弱小的獵物，給入門獵手練手。
//
// 結構完全沿用 /d/snow/npc/rabbit.c（雪亭練功場的野兔）：可被 kill、會還手，
// 但屬性極低、不主動攻擊路人(無 attitude=aggressive)，殺後只給少量 score(無錢可farm)。
// 差別：本獸略強於練功場野兔，且承「群獸朝靈」之亂，被林中戾氣所擾而焦躁。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("灰兔", ({ "gray hare", "grayhare", "hare", "huitu" }) );
	// 低屬性：根骨 8 → 形體上限約 40 點，弱於入門玩家，新手也打得過。
	set_attr("con", 8);
	set_attr("str", 6);
	set_attr("dex", 5);
	set_race("human");
	set_class("commoner");
	set_level(3);

	// 會用爪牙還手，但身手平平：徒手與閃躲都很低。
	set_skill("unarmed", 4);
	set_skill("dodge", 3);

	set("age", 1);
	set("gender", "female");
	set("long",
		"一隻毛色灰撲撲的山兔﹐比尋常野兔大上一圈﹐後腿精壯有力。\n"
		"近日林中那股戾氣攪得牠焦躁不安﹐一雙紅眼透著三分凶氣﹐受\n"
		"驚便豎起利齒亂咬﹐倒不似平日那般溫馴了。\n");
	// 殺後只給少量「江湖歷練(survive，升級用)」與「拳腳精熟(unarmed mastery)」經驗，
	// 純 score(gain_score)，無錢幣、無 carry_money，無法 farm money。
	set("bounty", ([
		"survive"         : 12,
		"unarmed mastery" : 6,
	]));
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
