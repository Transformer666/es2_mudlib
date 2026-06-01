// jackal.c -- 山豺，黑風山徑口成群出沒的猛獸，黑風山獵場最淺一級的獵物。
//
// 結構沿用 /d/hudao/wild/npc/madwolf.c（承 /d/snow/npc/rabbit.c）：可 kill、會
// 還手、不主動攻擊路人(無 attitude，由玩家 kill 起釁)，殺後只給 score(無錢)。
// 戰力定在 level 22 一線——接續野獸山林壓陣的黑熊(lvl20)往上一級，是備妥兵刃、
// 已有些火候的玩家堂堂正正打得過的對手(黑風山獵場的入門級)。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("山豺", ({ "mountain jackal", "jackal", "shanchai" }) );
	// 根骨 34 → 形體上限約 170 點，較黑熊(con30)略硬，群豺成隊、撕咬迅猛。
	set_attr("con", 34);
	set_attr("str", 30);
	set_attr("dex", 20);
	set_race("human");
	set_class("commoner");
	set_level(22);

	// 撕咬成群、身手矯捷，唯不諳吐納內力(無 force)：靠的是利齒與數量。
	set_skill("unarmed", 36);
	set_skill("dodge", 22);
	set_skill("parry", 20);

	set("age", 3);
	set("gender", "male");
	set("long",
		"一頭瘦長精悍的山豺﹐毛色焦黃中透著鐵青﹐脊背一道深褐的鬃\n"
		"線直貫尾根。牠口吻尖長﹐齒列森森﹐慣於成群結隊地在黑風山\n"
		"的亂石坡上奔突圍獵﹐連山羊野鹿都不放過。此刻牠弓著脊背﹐\n"
		"喉間滾出一串低沉而急促的咯咯聲﹐一雙黃綠的眼睛死死盯住了\n"
		"你﹐後腿微屈﹐隨時要竄上來撕咬。\n");
	// 純 score：江湖歷練(升級)、拳腳精熟、武術造詣、實戰經驗。無錢幣、無 carry_money。
	set("bounty", ([
		"survive"         : 280,
		"unarmed mastery" : 70,
		"martial art"     : 44,
		"combat"          : 22,
	]));
	setup();
}

// 奉陪到底、凶悍反擊（牠並不主動撲路人﹐由玩家 kill 起釁）。
int accept_fight(object ob)
{
	do_chat((: command, "say 山豺喉間滾出一串淒厲的咯咯聲﹐弓背豎鬃﹐獠牙森森地竄了上來﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
