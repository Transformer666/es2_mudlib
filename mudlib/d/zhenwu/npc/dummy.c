// dummy.c -- 草靶，振武校場的練習標靶，幾乎不還手。
// 結構沿用 /d/snow/npc/dummy.c（練功木人）：死靶、零閃躲、不主動、無錢可farm。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("草靶", ({ "caoba", "target", "dummy" }) );
	// 草紮的死靶不禁打：根骨 6 → 形體上限只有 30 點。
	set_attr("con", 6);
	set_attr("str", 5);
	set_attr("dex", 1);
	set_race("human");
	set_class("commoner");
	set_level(1);

	// 草靶是死靶：完全不閃躲，零技巧新手也百發百中。
	set_skill("dodge", 0);

	set("age", 1);
	set("gender", "male");
	set("long",
		"一具束草紮成的人形草靶﹐外罩一件破舊的號衣﹐靶身上槍孔刀\n"
		"痕密密麻麻﹐是軍士操演劈刺用的傢伙。\n");
	// 殺死後僅給極少量課目經驗（沿用 dummy.c 的上限數值），防止 farm。
	set("bounty/martial art", 8);
	set("bounty/martial mastery", 4);
	setup();
}

// 草靶被攻擊時只會搖晃，不主動還手（mirror dummy.c 的 accept_kill）。
int accept_kill(object ob)
{
	message_vision("$N被$n打得草屑紛飛。\n", this_object(), ob);
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
