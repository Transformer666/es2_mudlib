// stake.c -- 木樁假人，練武堂的練習標靶(假人)，幾乎不還手。
// 結構完全沿用 /d/snow/npc/dummy.c（練功木人）：死靶、零閃躲、不主動、無錢可farm。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("木樁假人", ({ "stake", "dummy stake", "wooden stake", "muzhuang" }) );
	// 比練功木人(con 6)耐打一些：根骨 12 → 形體上限約 60 點，
	// 讓玩家有夠久的時間捶打練兵器/拳腳，但仍遠弱於成熟玩家。
	set_attr("con", 12);
	set_attr("str", 5);
	set_attr("dex", 1);
	set_race("human");
	set_class("commoner");
	set_level(1);

	// 假人是死靶：完全不閃躲，零技巧新手也百發百中（mirror dummy.c）。
	set_skill("dodge", 0);

	set("age", 1);
	set("gender", "male");
	set("long",
		"一座立在練武堂中央的木樁假人﹐用粗木紮成人形﹐外面纏著厚厚\n"
		"的麻布﹐布面被無數拳腳磨出了深淺凹痕。它甚麼也不會﹐只是任\n"
		"人捶打﹐最適合初學者拿來練兵器與拳腳功夫。\n");
	// 殺死後給予極少量「江湖歷練」課目經驗(gain_score)，非錢幣，無法farm money。
	// 課目沿用 dummy.c / lieutenant.c 的 martial art / martial mastery，數值極小。
	set("bounty/martial art", 8);
	set("bounty/martial mastery", 4);
	setup();
}

// 假人被攻擊時只會搖晃，不主動還手（mirror dummy.c 的 accept_kill）。
int accept_kill(object ob)
{
	message_vision("$N被$n打得搖搖晃晃。\n", this_object(), ob);
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
