// frostfox.c -- 霜林靈狐，秋一谷霜雪藥圃一帶守藥的靈狐，狡黠迅捷、頗難纏。
//
// 結構沿用 /d/langwo/npc/azurewolf.c（承 /d/heifeng/npc/greywolf.c → rabbit.c）：
// 可 kill、會還手、不主動攻擊路人(無 attitude)，殺後只給 score(無錢)。戰力定在
// level 42 一線——秋一谷藥圃的中階靈獸，較狼窩谷青狼(26)更猛，是本獵場的入門對手。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("霜林靈狐", ({ "frost fox", "frostfox", "fox", "shuanglin linghu" }) );
	// 根骨 48 → 形體上限約 240 點；另以 advance_stat 加厚氣血，撲擊迅捷、耐戰。
	set_attr("con", 48);
	set_attr("str", 40);
	set_attr("dex", 38);
	set_race("human");
	set_class("commoner");
	set_level(42);

	// 守藥靈狐：撲擊狡黠、爪牙俱利，閃躲格外了得，已諳吐納靈氣。
	set_skill("unarmed", 70);
	set_skill("dodge", 56);
	set_skill("parry", 48);
	set_skill("force", 50);

	// 厚其氣血，使之耐打、有來有往（量級貼合 lv42 中階靈獸）。
	advance_stat("kee", 120);

	set("age", 6);
	set("gender", "female");
	set("long",
		"一頭通體火紅的靈狐﹐毛色赤艷如焰﹐在這滿地的白霜間紅得\n"
		"格外刺眼。牠生得格外伶俐狡黠﹐一雙琥珀色的眼睛精光流轉﹐\n"
		"九尾蓬鬆如雲﹐尾尖一抹雪白。牠世代守在這秋一谷的藥圃裡看\n"
		"護靈草﹐久浸谷中靈氣﹐已隱隱通了幾分靈性。此刻牠壓低了身\n"
		"子﹐尾尖微微抖動﹐琥珀色的眼睛緊緊盯著你﹐喉間滾出一串低\n"
		"沉而警惕的嗚咽——分明是把你當作了來盜採靈草的不速之客。\n");
	// 純 score：江湖歷練(升級)、拳腳精熟、武術造詣、武學之道、實戰經驗。無錢幣。
	set("bounty", ([
		"survive"         : 560,
		"unarmed mastery" : 130,
		"martial art"     : 90,
		"martial mastery" : 50,
		"combat"          : 56,
	]));
	setup();
}

// 奉陪到底、凶悍反擊（牠並不主動撲路人﹐由玩家 kill 起釁）。
int accept_fight(object ob)
{
	do_chat((: command, "say 霜林靈狐九尾倏地炸開﹐尾尖一抖﹐化作一道赤紅殘影自側翼撲擊而至﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
