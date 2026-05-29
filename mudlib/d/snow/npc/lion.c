// lion.c -- 石獅子，練武堂的練習標靶(石獅)，紋風不動任人捶打。
// 結構完全沿用 /d/snow/npc/dummy.c（練功木人）：死靶、零閃躲、不主動、無錢可farm。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("石獅子", ({ "lion", "stone lion", "stonelion", "shishi" }) );
	// 石頭打造，比假人更耐打：根骨 16 → 形體上限約 80 點，
	// 經得起久練，但既不閃也不還手，零技巧也打得中。
	set_attr("con", 16);
	set_attr("str", 5);
	set_attr("dex", 1);
	set_race("human");
	set_class("commoner");
	set_level(1);

	// 石獅是死靶：完全不閃躲（mirror dummy.c）。
	set_skill("dodge", 0);

	set("age", 1);
	set("gender", "male");
	set("long",
		"一頭蹲踞在練武堂角落的石獅子﹐鬃毛與爪牙都雕得栩栩如生﹐\n"
		"石身被歷代習武之人捶得處處發亮。它紋風不動﹐任憑你拳打腳\n"
		"踢﹐是鎮上武人磨練兵器與拳腳的好標靶。\n");
	// 殺死後給予極少量「江湖歷練」課目經驗(gain_score)，非錢幣，無法farm money。
	set("bounty/martial art", 8);
	set("bounty/martial mastery", 4);
	setup();
}

// 石獅被攻擊時只是石屑紛飛，不主動還手（mirror dummy.c 的 accept_kill）。
int accept_kill(object ob)
{
	message_vision("$N被$n打得石屑紛飛。\n", this_object(), ob);
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
