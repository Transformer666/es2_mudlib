// dummy.c -- 木人樁，虎刀門演武場的練習標靶，幾乎不還手。
// 結構沿用 /d/snow/npc/dummy.c（練功木人）：死靶、零閃躲、不主動、無錢可farm。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("木人樁", ({ "muren", "stake", "dummy" }) );
	// 死靶屬性壓得極低：根骨 10 → 形體上限約 50 點，夠捶打又遠弱於玩家。
	set_attr("con", 10);
	set_attr("str", 5);
	set_attr("dex", 1);
	set_race("human");
	set_class("commoner");
	set_level(1);

	// 木人樁是死靶：完全不閃躲，零技巧新手也百發百中。
	set_skill("dodge", 0);

	set("age", 1);
	set("gender", "male");
	set("long",
		"一根碗口粗的老松木人樁﹐樁身上密佈著縱橫交錯的劈砍刀痕﹐\n"
		"刀口深峻齊整﹐可見虎刀門弟子下刀之狠。它任人劈砍﹐不會還手。\n");
	// 殺死後僅給極少量課目經驗（沿用 dummy.c 的上限數值），防止 farm。
	set("bounty/martial art", 8);
	set("bounty/martial mastery", 4);
	setup();
}

// 木人樁被攻擊時只會搖晃，不主動還手（mirror dummy.c 的 accept_kill）。
int accept_kill(object ob)
{
	message_vision("$N被$n打得搖搖晃晃。\n", this_object(), ob);
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
