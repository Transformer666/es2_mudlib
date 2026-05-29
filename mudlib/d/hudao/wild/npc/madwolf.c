// madwolf.c -- 瘋狼，野獸山林獸窟深處的猛獸，凶悍迅捷，深受戾氣蠱惑。
//
// 結構沿用 /d/snow/npc/rabbit.c：可 kill、會還手、不主動攻擊路人(無 attitude)，
// 殺後只給 score(無錢)。承 deepwoods「猛獸朝靈」之伏筆，已是頗硬的對手。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("瘋狼", ({ "mad wolf", "madwolf", "wolf", "fenglang" }) );
	// 根骨 24 → 形體上限約 120 點，又快又狠，須有相當火候的玩家方能應付。
	set_attr("con", 24);
	set_attr("str", 22);
	set_attr("dex", 20);
	set_race("human");
	set_class("commoner");
	set_level(16);

	// 凶猛迅捷：撕咬、閃躲、拆招、內力俱佳。
	set_skill("unarmed", 26);
	set_skill("dodge", 22);
	set_skill("parry", 20);
	set_skill("force", 22);

	set("age", 5);
	set("gender", "male");
	set("long",
		"一頭脊毛賁張的青灰巨狼﹐瘦骨嶙峋卻筋健如鐵﹐口角垂著涎沫﹐\n"
		"一雙眼睛紅得像要滴出血來。那股自天靈山漫來的青黑戾氣已浸\n"
		"透了牠的魂魄﹐使牠忘了饑飽痛楚﹐只知一味嗜殺﹐喉間滾出的\n"
		"低嗥裡﹐竟透著幾分不似走獸的怨毒。\n");
	// 純 score：江湖歷練(升級)、拳腳精熟、武術造詣、武學之道、實戰經驗。無錢幣。
	set("bounty", ([
		"survive"         : 140,
		"unarmed mastery" : 40,
		"martial art"     : 28,
		"martial mastery" : 16,
		"combat"          : 18,
	]));
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
