// blackbear.c -- 黑熊「獸群之首」，野獸山林最深處盤踞的巨獸，群獸隱隱以牠為首。
//
// 結構沿用 /d/snow/npc/rabbit.c：可 kill、會還手、不主動攻擊路人(無 attitude)，
// 殺後只給 score(無錢)。為本區最硬的對手，隱隱呼應天靈山摩雲一脈(純劇情伏筆，
// 牠仍是凡間血肉、可被擊殺)。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("黑熊", ({ "black bear", "blackbear", "bear", "heixiong" }) );
	set("nickname", "獸群之首");
	// 根骨 30 → 形體上限約 150 點，氣力驚人、皮堅肉厚，乃本區壓陣的巨獸。
	set_attr("con", 30);
	set_attr("str", 28);
	set_attr("dex", 16);
	set_race("human");
	set_class("commoner");
	set_level(20);

	// 力大勢沉：熊掌拍擊勢大力沉，拆招與內力俱強，唯身形稍鈍。
	set_skill("unarmed", 32);
	set_skill("dodge", 18);
	set_skill("parry", 26);
	set_skill("force", 28);

	set("age", 9);
	set("gender", "male");
	set("long",
		"一頭立起來比人還高出兩個頭的玄色巨熊﹐渾身黑毛油亮﹐胸前\n"
		"一彎月牙似的白斑﹐熊掌寬若蒲扇﹐利爪森然。林中群獸狂奔朝\n"
		"靈﹐唯牠盤踞窟中巋然不動﹐眾獸繞行而不敢近﹐隱隱奉牠為\n"
		"首。牠那雙小眼裡燃著一點幽幽的青芒﹐似與天靈山深處某個更\n"
		"龐大的存在遙遙相應﹐令人望之心折。\n");
	// 純 score：江湖歷練(升級)、拳腳精熟、武術造詣、武學之道、實戰經驗。無錢幣、無 carry_money。
	set("bounty", ([
		"survive"         : 240,
		"unarmed mastery" : 60,
		"martial art"     : 40,
		"martial mastery" : 28,
		"combat"          : 30,
	]));
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
