// oldsnake.c -- 老澤蛇，盤踞婁縣蛇潭潭底、碗口粗細的水澤巨蛇，蛇潭之霸。
//
// 結構沿用 /d/heifeng/npc/greywolf.c：可 kill、會還手、不主動攻擊路人(無 attitude)，
// 殺後只給 score(無錢)。戰力定在 level 26 一線——婁縣水澤獵場的最強對手、上段把關，
// 身懷劇毒、纏絞剛猛，是頗硬的對手。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("老澤蛇", ({ "old marsh snake", "oldsnake", "marsh snake", "snake", "laozeshe" }) );
	// 根骨 40 → 形體上限約 200 點；另以 advance_stat 加厚氣血﹐丈餘巨蛇極耐戰。
	set_attr("con", 40);
	set_attr("str", 36);
	set_attr("dex", 30);
	set_race("human");
	set_class("commoner");
	set_level(26);

	// 纏絞剛猛、吐信迅捷、閃躲拆招俱熟、內力中平（盤踞蛇潭多年的巨蛇）。
	set_skill("unarmed", 46);
	set_skill("dodge", 30);
	set_skill("parry", 28);
	set_skill("force", 22);

	// 厚其氣血﹐使之耐打、有來有往（量近黑風蒼狼一線）。
	advance_stat("kee", 40);

	set("age", 15);
	set("gender", "male");
	set("long",
		"一條碗口粗細的老澤蛇﹐通體烏黑泛著幽幽的青光﹐少說也有丈餘\n"
		"來長﹐盤踞在蛇潭的潭底﹐是這水澤最毒最大的蛇物。牠時而昂起\n"
		"半截身子在水面遊弋﹐三角扁頭吐著鮮紅的信子﹐一雙凶睛冷冷地\n"
		"盯著岸上的生人﹐透著森森的寒意。牠纏絞起來力大無窮﹐毒牙一\n"
		"啖便是要命的劇毒﹐縣裡的漁戶提起牠來﹐沒一個不變色搖頭的。\n");
	// 純 score：江湖歷練(升級)、拳腳精熟、武術造詣、武學之道、實戰經驗。無錢幣。
	set("bounty", ([
		"survive"         : 400,
		"unarmed mastery" : 100,
		"martial art"     : 64,
		"martial mastery" : 32,
		"combat"          : 34,
	]));
	setup();
}

// 不主動撲路人﹐由玩家 kill 起釁；昂首纏撲。
int accept_fight(object ob)
{
	do_chat((: command, "say 老澤蛇昂起半截烏黑的身子﹐三角扁頭吐著信子﹐凶睛一厲﹐挾著一身寒毒纏撲而上﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
