// hungrywolf.c -- 餓狼，狼窩谷亂石狼坡一帶伏踞的野狼，久餓凶狠，較灰狼更難纏。
//
// 結構沿用 /d/wuling/npc/direwolf.c（承 /d/hudao/wild/npc/madwolf.c → rabbit.c）：
// 可 kill、會還手、不主動攻擊路人(無 attitude)，殺後只給 score(無錢)。戰力定在
// level 20 一線——較灰狼(14)更硬、撲擊更狠，是狼窩谷獵場的中段對手。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("餓狼", ({ "hungry wolf", "hungrywolf", "wolf", "elang" }) );
	// 根骨 30 → 形體上限約 150 點，餓極不要命，皮糙肉厚、耐戰。
	set_attr("con", 30);
	set_attr("str", 28);
	set_attr("dex", 22);
	set_race("human");
	set_class("commoner");
	set_level(20);

	// 餓極狂猛、略諳吐納：撕咬、閃躲、拆招俱佳，內力中平。
	set_skill("unarmed", 34);
	set_skill("dodge", 22);
	set_skill("parry", 24);
	set_skill("force", 22);

	// 厚其氣血，使之耐打、有來有往（量輕，參蒼狼 advance_stat 之法遠減之）。
	advance_stat("kee", 30);

	set("age", 4);
	set("gender", "male");
	set("long",
		"一頭瘦骨嶙峋的餓狼﹐周身的灰毛因久餓而失了光澤﹐肋骨根根\n"
		"分明﹐一雙眼睛卻幽幽地泛著飢渴的綠光。牠久未飽食﹐撲起人\n"
		"來不要命﹐較尋常灰狼更其凶狠難纏。此刻牠伏在亂石之後﹐脊\n"
		"毛賁張﹐口角垂著涎沫﹐喉間滾出一聲低沉的威嗥﹐分明已將你\n"
		"視作了一頓久候的飽餐。\n");
	// 純 score：江湖歷練(升級)、拳腳精熟、武術造詣、武學之道、實戰經驗。無錢幣。
	set("bounty", ([
		"survive"         : 240,
		"unarmed mastery" : 60,
		"martial art"     : 40,
		"martial mastery" : 28,
		"combat"          : 30,
	]));
	setup();
}

// 奉陪到底、凶悍反擊（牠並不主動撲路人﹐由玩家 kill 起釁）。
int accept_fight(object ob)
{
	do_chat((: command, "say 餓狼脖頸一沉﹐發出一聲飢渴的威嗥﹐弓身豎毛﹐疾撲而上﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
