// dummy.c -- 玄鐵樁，青邪宮演武場的練習標靶，幾乎不還手。
// 結構沿用 /d/snow/npc/dummy.c（練功木人）：死靶、零閃躲、不主動、無錢可farm。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("玄鐵樁", ({ "xuantiezhuang", "stake", "dummy" }) );
	// 玄鐵鑄的死靶比木樁耐打一些：根骨 12 → 形體上限約 60 點。
	set_attr("con", 12);
	set_attr("str", 5);
	set_attr("dex", 1);
	set_race("human");
	set_class("commoner");
	set_level(1);

	// 玄鐵樁是死靶：完全不閃躲，零技巧新手也百發百中。
	set_skill("dodge", 0);

	set("age", 1);
	set("gender", "male");
	set("long",
		"一根深深釘入黑磚的玄鐵樁子﹐樁身上密佈著縱橫的刀痕杖印﹐\n"
		"可見青邪宮弟子功力之剛猛。它任人捶打﹐不會還手。\n");
	// 殺死後僅給極少量課目經驗（沿用 dummy.c 的上限數值），防止 farm。
	set("bounty/martial art", 8);
	set("bounty/martial mastery", 4);
	setup();
}

// 玄鐵樁被攻擊時只會鏗鏗作響，不主動還手（mirror dummy.c 的 accept_kill）。
int accept_kill(object ob)
{
	message_vision("$N被$n打得鏗然作響。\n", this_object(), ob);
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
