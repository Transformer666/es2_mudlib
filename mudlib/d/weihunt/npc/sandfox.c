// sandfox.c -- 沙狐，衛國邊塞亂石坡上機警狡黠的塞外赤狐。
//
// 結構沿用 /d/heifeng/npc/greywolf.c：可 kill、會還手、不主動攻擊路人(無 attitude)，
// 殺後只給 score(無錢)。戰力定在 level 24 一線——衛國邊塞獵場的入門對手，身手靈巧。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("沙狐", ({ "sand fox", "sandfox", "fox", "shahu" }) );
	set_attr("con", 26);
	set_attr("str", 26);
	set_attr("dex", 34);
	set_race("human");
	set_class("commoner");
	set_level(24);

	// 機警狡黠、閃竄極靈、撕咬尖利﹐內力中平。
	set_skill("unarmed", 36);
	set_skill("dodge", 38);
	set_skill("parry", 26);
	set_skill("force", 20);

	set("age", 3);
	set("gender", "female");
	set("long",
		"一隻塞外的赤狐﹐生得一身火紅油亮的皮毛﹐尖嘴利爪﹐三角眼裡\n"
		"閃著機警狡黠的幽光。牠慣在邊塞的亂石間刨洞做窠﹐晨昏出獵﹐\n"
		"身手快得像一道紅影﹐叼了獵物便倏地鑽進石縫。被逼急了﹐牠也\n"
		"會弓背豎毛﹐齜出一口尖牙凶狠反撲﹐絕非好相與的角色。\n");
	// 純 score：江湖歷練(升級)、拳腳精熟、武術造詣、武學之道、實戰經驗。無錢幣。
	set("bounty", ([
		"survive"         : 320,
		"unarmed mastery" : 80,
		"martial art"     : 52,
		"martial mastery" : 26,
		"combat"          : 30,
	]));
	setup();
}

// 不主動撲路人﹐由玩家 kill 起釁；機警反撲。
int accept_fight(object ob)
{
	do_chat((: command, "say 沙狐倏地弓背豎毛﹐三角眼裡凶光一閃﹐齜牙反撲而上﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
