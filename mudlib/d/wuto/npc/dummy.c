// dummy.c -- 銅人，武陀灸堂演武場的試針標靶，幾乎不還手。
// 結構沿用 /d/snow/npc/dummy.c（練功木人）：死靶、零閃躲、不主動、無錢可farm。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("銅人", ({ "tongren", "bronze man", "dummy" }) );
	// 銅鑄的死靶比木樁耐打一些：根骨 12 → 形體上限約 60 點。
	set_attr("con", 12);
	set_attr("str", 5);
	set_attr("dex", 1);
	set_race("human");
	set_class("commoner");
	set_level(1);

	// 銅人是死靶：完全不閃躲，零技巧新手也百發百中。
	set_skill("dodge", 0);

	set("age", 1);
	set("gender", "male");
	set("long",
		"一具半人高的銅人﹐通體刻著經絡穴位﹐每一處穴道旁皆以小字\n"
		"標注名目﹐是醫者辨穴試針的法器﹐任人施針捶打。\n");
	// 殺死後僅給極少量課目經驗（沿用 dummy.c 的上限數值），防止 farm。
	set("bounty/martial art", 8);
	set("bounty/martial mastery", 4);
	setup();
}

// 銅人被攻擊時只會搖晃，不主動還手（mirror dummy.c 的 accept_kill）。
int accept_kill(object ob)
{
	message_vision("$N被$n打得嗡嗡作響。\n", this_object(), ob);
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
