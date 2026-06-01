// leopard.c -- 巖豹，黑風山絕壁與密林間出沒的猛獸，迅捷剽悍，已是頗硬的對手。
//
// 結構沿用 /d/hudao/wild/npc/madwolf.c（承 /d/snow/npc/rabbit.c）：可 kill、會
// 還手、不主動攻擊路人(無 attitude)，殺後只給 score(無錢)。戰力定在 level 31 一線
// ——較蒼狼(26)更猛，撲擊迅疾，是黑風山獵場接近高段的對手。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("巖豹", ({ "rock leopard", "leopard", "yanbao" }) );
	// 根骨 48 → 形體上限約 240 點；另以 advance_stat 加厚氣血，撲擊兇猛、極耐戰。
	set_attr("con", 48);
	set_attr("str", 40);
	set_attr("dex", 30);
	set_race("human");
	set_class("commoner");
	set_level(31);

	// 撲擊迅疾、爪牙俱利：徒手與閃躲俱高，拆招、內力亦不弱。
	set_skill("unarmed", 62);
	set_skill("dodge", 40);
	set_skill("parry", 38);
	set_skill("force", 36);

	// 厚其氣血，使之耐打、有來有往（量仍遠輕於魚鐵山 lvl40 的 250）。
	advance_stat("kee", 90);

	set("age", 6);
	set("gender", "female");
	set("long",
		"一頭毛色青灰、遍體墨斑的巖豹﹐伏踞在絕壁的石稜之上﹐周身\n"
		"的線條精悍而充滿爆發之力。牠的斑紋與這黑風山的青黑岩壁渾\n"
		"然一色﹐若非那雙幽幽泛綠的眼睛﹐幾乎教人辨不出。牠是攀崖\n"
		"踏壁的好手﹐撲擊起來迅如閃電﹐尋常獵戶遇上牠﹐往往連豹影\n"
		"都沒看清﹐咽喉便已洞穿。此刻牠壓低了身子﹐尾尖微微抖動﹐\n"
		"正蓄勢欲撲。\n");
	// 純 score：江湖歷練(升級)、拳腳精熟、武術造詣、武學之道、實戰經驗。無錢幣。
	set("bounty", ([
		"survive"         : 540,
		"unarmed mastery" : 120,
		"martial art"     : 80,
		"martial mastery" : 48,
		"combat"          : 44,
	]));
	setup();
}

// 奉陪到底、凶悍反擊（牠並不主動撲路人﹐由玩家 kill 起釁）。
int accept_fight(object ob)
{
	do_chat((: command, "say 巖豹壓低身子﹐尾尖一抖﹐倏地化作一道青灰殘影撲擊而至﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
