// dummy.c -- 練功木人，雪亭練功場的練習標靶，幾乎不還手。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("練功木人", ({ "dummy", "muren" }) );
	// 故意把屬性壓得極低：根骨 6 → 形體上限只有 30 點，
	// 比剛入門的玩家(根骨 13-18，形體 65-90)弱得多。
	set_attr("con", 6);
	set_attr("str", 5);
	set_attr("dex", 1);
	set_race("human");
	set_class("commoner");
	set_level(1);

	// 木人是死靶：完全不閃躲，零技巧新手也百發百中。
	set_skill("dodge", 0);

	set("age", 1);
	set("gender", "male");
	set("long",
		"一個用粗木紮成的練功木人﹐外面纏著厚厚的麻布﹐布上佈滿了\n"
		"拳腳留下的凹痕。它就立在練功場中央﹐任人捶打。\n");
	// 殺死後給予少量經驗值，用來驗證戰鬥/升級的循環。
	// 課目沿用 lieutenant.c 的 martial art / martial mastery，但數值極小。
	set("bounty/martial art", 8);
	set("bounty/martial mastery", 4);
	setup();
}

// 木人被攻擊時只會搖晃，不主動還手太兇。
int accept_kill(object ob)
{
	message_vision("$N被$n打得搖搖晃晃。\n", this_object(), ob);
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
