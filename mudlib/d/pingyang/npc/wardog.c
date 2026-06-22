// wardog.c -- 看寨惡犬，山賊豢養來看守山寨、撕咬來犯者的猛犬，平陽半山與山寨一帶
//             較山賊更兇的獵物。
//
// 結構沿用 /d/heifeng/npc/greywolf.c（承 rabbit.c）：可 kill、會還手、不主動攻擊路人
// (無 attitude，由玩家 kill 起釁)，殺後只給 score(野獸無錢、無 carry_money)。戰力定在
// level 48 一線——較山賊(42)更猛，撲擊兇狠、皮糙肉厚，是平陽山獵場中後段、近賊寨外圍的
// 對手，仍輕於寨主公孫一笑。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("看寨惡犬", ({ "war dog", "wardog", "guard dog", "edog" }) );
	// 根骨 52 → 形體上限約 260 點；另以 advance_stat 加厚氣血，皮糙肉厚、極耐戰。
	set_attr("con", 52);
	set_attr("str", 44);
	set_attr("dex", 34);
	set_race("human");
	set_class("commoner");
	set_level(48);

	// 看寨惡犬撲擊兇狠、爪牙俱利，身手矯捷，略諳吐納：是一場兇險的惡鬥。
	set_skill("unarmed", 80);
	set_skill("dodge", 44);
	set_skill("parry", 50);
	set_skill("force", 50);

	// 加厚其氣血，使之耐戰、有來有往（量輕於 boss 與雪吟莊主一系）。
	advance_stat("kee", 100);

	set("age", 4);
	set("gender", "male");
	set("long",
		"一頭山賊豢養來看寨的惡犬﹐生得身形高大、骨架粗壯﹐周身覆\n"
		"著一層糾結的黑黃硬毛。牠口吻寬闊﹐獠牙森森﹐涎水自牙縫間長\n"
		"流而下﹐一雙血紅的眼睛裡滿是兇戾之氣。這畜生被山賊用鐵鏈拴\n"
		"養、以生肉餵兇﹐專一撕咬闖寨的生人﹐撲起人來不要命。此刻牠\n"
		"弓著脊背﹐喉間滾出一串低沉的怒吼﹐後腿微屈﹐隨時要竄上來撕咬。\n");
	// 純 score：江湖歷練(升級)、拳腳精熟、武術造詣、實戰經驗。無錢幣、無 carry_money。
	set("bounty", ([
		"survive"         : 720,
		"unarmed mastery" : 150,
		"martial art"     : 100,
		"martial mastery" : 55,
		"combat"          : 55,
	]));
	setup();
}

// 奉陪到底、兇悍反擊（牠並不主動撲路人﹐由玩家 kill 起釁）。
int accept_fight(object ob)
{
	do_chat((: command, "say 看寨惡犬喉間滾出一串淒厲的怒吼﹐弓背豎毛﹐獠牙森森地撲了上來﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
