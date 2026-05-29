// wildboar.c -- 野豬，野獸山林山坡上的猛獸，獠牙衝撞，已有相當威脅。
//
// 結構沿用 /d/snow/npc/rabbit.c：可 kill、會還手、不主動攻擊路人(無 attitude)，
// 殺後只給 score(無錢)。承 deepwoods「野豬成群朝靈」之伏筆，較野猴難纏許多。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("野豬", ({ "wild boar", "wildboar", "boar", "yezhu" }) );
	// 根骨 18 → 形體上限約 90 點，皮糙肉厚、力大難纏，須有些拳腳的玩家才打得過。
	set_attr("con", 18);
	set_attr("str", 20);
	set_attr("dex", 9);
	set_race("human");
	set_class("commoner");
	set_level(10);

	// 蠻力衝撞型：徒手與內力不低，閃躲笨拙；偶爾以獠牙格開來招。
	set_skill("unarmed", 16);
	set_skill("dodge", 8);
	set_skill("parry", 10);
	set_skill("force", 12);

	set("age", 4);
	set("gender", "male");
	set("long",
		"一頭黑鬃野豬﹐肩背隆起如小丘﹐一對焦黃的獠牙森森外露﹐獠\n"
		"牙上猶沾著新蹭的樹皮與血沫。牠教林中那股青黑戾氣激得雙目\n"
		"赤紅﹐喉間不住發出粗重的噴鳴﹐前蹄刨地﹐隨時要朝擋路的活\n"
		"物沒命地衝撞過來。\n");
	// 純 score：江湖歷練(升級)、拳腳精熟、武術造詣、實戰經驗。無錢幣、無 carry_money。
	set("bounty", ([
		"survive"         : 70,
		"unarmed mastery" : 26,
		"martial art"     : 18,
		"combat"          : 10,
	]));
	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
