// pillar.c -- 石柱，練武堂的練習標靶(石柱)，最耐打的死靶。
// 結構完全沿用 /d/snow/npc/dummy.c（練功木人）：死靶、零閃躲、不主動、無錢可farm。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("石柱", ({ "pillar", "stone pillar", "stonepillar", "shizhu" }) );
	// 整根石柱，最耐打：根骨 20 → 形體上限約 100 點，
	// 適合一口氣長練，但同樣不閃不還手。
	set_attr("con", 20);
	set_attr("str", 5);
	set_attr("dex", 1);
	set_race("human");
	set_class("commoner");
	set_level(1);

	// 石柱是死靶：完全不閃躲（mirror dummy.c）。
	set_skill("dodge", 0);

	set("age", 1);
	set("gender", "male");
	set("long",
		"一根半人合抱的青石柱﹐深深埋在練武堂的夯土地裡﹐柱身遍佈\n"
		"著拳印掌痕。它沉默地矗立著﹐任你千捶百打也不挪一分﹐是練\n"
		"硬功與兵器最耐久的標靶。\n");
	// 殺死後給予極少量「江湖歷練」課目經驗(gain_score)，非錢幣，無法farm money。
	set("bounty/martial art", 8);
	set("bounty/martial mastery", 4);
	setup();
}

// 石柱被攻擊時只是震落塵土，不主動還手（mirror dummy.c 的 accept_kill）。
int accept_kill(object ob)
{
	message_vision("$N被$n打得簌簌震落塵土。\n", this_object(), ob);
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
