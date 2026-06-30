// riverlair.c -- 蘆蕩水獺，羿水漁港外蘆葦蕩裡成群出沒的兇悍水獺。
//
// 結構沿用 /d/heifeng/npc/greywolf.c（承 /d/snow/npc/rabbit.c）：可 kill、會還手、
// 不主動攻擊路人(無 attitude)，殺後只給 score(無錢)。戰力定在 level 18 一線——
// 是羿水漁港這片水鄉獵場的入門對手，較蒼狼(26)輕，合 lv 15-35 區間的低段。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("蘆蕩水獺", ({ "river otter", "otter", "shuita" }) );
	// 水獸：靈巧迅捷(dex 高)，氣力中平，皮毛滑膩難纏。
	set_attr("con", 28);
	set_attr("str", 26);
	set_attr("dex", 32);
	set_race("human");
	set_class("commoner");
	set_level(18);

	// 撕咬迅猛、極善閃躲；不諳內力。
	set_skill("unarmed", 30);
	set_skill("dodge", 30);
	set_skill("parry", 18);
	set_skill("force", 10);

	// 略厚其氣血，使之耐打、有來有往（量輕，較蒼狼遠輕）。
	advance_stat("kee", 20);

	set("age", 3);
	set("gender", "male");
	set("long",
		"一頭肥碩兇蠻的水獺﹐周身覆著一層油亮滑膩的褐色皮毛﹐水\n"
		"珠在毛尖上滾來滾去。牠生得比尋常溪邊的水獺大上一圈﹐露出\n"
		"的兩排尖牙白森森的。這蘆蕩裡的水獺成群結隊﹐專咬壞漁人的\n"
		"網、偷食簍中之魚﹐連單身的漁人也敢撲咬。牠弓著背伏在爛泥\n"
		"灘上﹐一雙圓溜溜的眼珠滴溜溜地盯著你﹐喉間咯咯地威嚇著。\n");
	// 純 score：江湖歷練(升級)、拳腳精熟、武術造詣、實戰經驗。無錢幣。
	set("bounty", ([
		"survive"         : 200,
		"unarmed mastery" : 50,
		"martial art"     : 35,
		"combat"          : 20,
	]));
	setup();
}

// 奉陪到底、凶悍反擊（牠並不主動撲路人﹐由玩家 kill 起釁）。
int accept_fight(object ob)
{
	do_chat((: command, "say 蘆蕩水獺喉間咯咯一陣威嚇﹐露出白森森的尖牙﹐弓背疾撲而上﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
