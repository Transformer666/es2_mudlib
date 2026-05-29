// wildape.c -- 野猴(白猴)，野獸山林林徑上成群出沒的獵物，比灰兔難纏些。
//
// 結構沿用 /d/snow/npc/rabbit.c：可 kill、會還手、不主動攻擊路人(無 attitude)，
// 殺後只給 score(無錢)。承老松林深處(deepwoods)「白猴成群朝靈」之伏筆。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("野猴", ({ "wild ape", "wildape", "ape", "monkey", "yehou" }) );
	// 根骨 11 → 形體上限約 55 點，身手較靈活，比灰兔更會閃。
	set_attr("con", 11);
	set_attr("str", 9);
	set_attr("dex", 12);
	set_race("human");
	set_class("commoner");
	set_level(5);

	// 山猴手腳靈巧：徒手與閃躲都比灰兔高，偶爾還會撥開來拳。
	set_skill("unarmed", 8);
	set_skill("dodge", 10);
	set_skill("parry", 5);

	set("age", 2);
	set("gender", "male");
	set("long",
		"一隻毛色灰白的山猴﹐蹲在枝椏間齜牙咧嘴﹐一雙眼睛滴溜溜地\n"
		"打量著你。牠原是松林裡最頑皮的活物﹐近日卻教那股戾氣勾得\n"
		"性子暴烈﹐動輒呲牙撲抓﹐成群結隊地朝著北邊天靈山的方向竄\n"
		"去﹐見了生人也不再躲閃﹐反倒張牙舞爪起來。\n");
	// 純 score：江湖歷練(升級)、拳腳精熟、武術造詣。無錢幣、無 carry_money。
	set("bounty", ([
		"survive"         : 28,
		"unarmed mastery" : 12,
		"martial art"     : 8,
	]));
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
