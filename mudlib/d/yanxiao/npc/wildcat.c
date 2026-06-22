// wildcat.c -- 莽林山狸，焱硝村外林徑邊竄出的野獸，莽林獵場最淺一級。
//
// 結構沿用 /d/heifeng/npc/greywolf.c（承 madwolf → rabbit）：可 kill、會還
// 手、不主動攻擊路人(無 attitude，由玩家 kill 起釁)，殺後只給 score(無錢)。
// 戰力定在 level 20 一線——莽林填充獵場的入門對手，過路客練手之用。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("山狸", ({ "wild cat", "wildcat", "cat", "shanli" }) );
	set("nickname", "山狸");
	// 根骨 28 → 形體上限約 140 點；身手矯捷、利爪快牙，耐戰中平。
	set_attr("con", 28);
	set_attr("str", 24);
	set_attr("dex", 30);
	set_race("human");
	set_class("commoner");
	set_level(20);

	// 撲咬迅疾、閃躲靈動，略諳拆招，內力中平。
	set_skill("unarmed", 32);
	set_skill("dodge", 28);
	set_skill("parry", 22);
	set_skill("force", 18);

	set("age", 3);
	set("gender", "female");
	set("long",
		"一頭焦黃斑紋的莽林山狸﹐體形比尋常家貓大上數倍﹐四肢精瘦\n"
		"而矯健﹐尾巴粗長﹐毛色枯黃間雜著一道道深褐的斑紋﹐正好藏\n"
		"身在這莽林的草木枯葉之間。牠弓著脊背﹐豎起一身炸毛﹐喉間\n"
		"發出咻咻的低嘶﹐一雙琥珀色的豎瞳死死盯住了你﹐利爪扣進腐\n"
		"葉﹐隨時要竄上來撕咬。\n");
	// 純 score：江湖歷練(升級)、拳腳精熟、武術造詣、實戰經驗。無錢幣。
	set("bounty", ([
		"survive"         : 230,
		"unarmed mastery" : 52,
		"martial art"     : 38,
		"combat"          : 22,
	]));
	setup();
}

// 奉陪到底、凶悍反擊（牠並不主動撲路人﹐由玩家 kill 起釁）。
int accept_fight(object ob)
{
	do_chat((: command, "say 山狸喉間咻咻低嘶﹐弓背炸毛﹐倏地竄起﹐利爪直撲面門﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
