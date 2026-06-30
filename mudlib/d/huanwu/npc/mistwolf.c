// mistwolf.c -- 霧狼，幻霧森林霧深處出沒的灰白野狼，獵場中段獵物。
//
// 結構沿用 /d/langwo/npc/graywolf.c：可 kill、會還手、不主動攻擊路人(無
// attitude)，殺後只給 score(無錢)。戰力定在 level 20 一線——承林緣野豬(lvl16)
// 往上一級，毛色灰白如霧、來去無聲，是新手村群獵場的中段對手。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("霧狼", ({ "mist wolf", "mistwolf", "wolf", "wulang" }) );
	// 根骨 28 → 形體上限約 140 點，較野豬硬，更兼身手矯捷、來去如霧。
	set_attr("con", 28);
	set_attr("str", 26);
	set_attr("dex", 24);
	set_race("human");
	set_class("commoner");
	set_level(20);

	// 撕咬迅捷、慣藉濃霧掩身偷襲：徒手、閃拆俱佳，內力中平。
	set_skill("unarmed", 32);
	set_skill("dodge", 24);
	set_skill("parry", 22);
	set_skill("force", 18);

	// 厚其氣血，使之耐戰、有來有往（量參狼窩谷灰狼，略加）。
	advance_stat("kee", 20);

	set("age", 4);
	set("gender", "male");
	set("long",
		"一頭毛色灰白如霧的野狼﹐在這彌天的白霧裡幾乎隱形﹐唯有一\n"
		"雙幽幽的綠眼與森森的獠牙﹐在霧中時隱時現。牠是這幻霧森林\n"
		"裡的常客﹐慣藉著濃霧掩身﹐悄無聲息地兜到獵物背後﹐冷不防\n"
		"撲上來咬斷喉嚨。此刻牠弓著脊背﹐喉間滾出一串壓得極低的嗚\n"
		"咽﹐繞著你緩緩踱步﹐隨時要竄進霧裡再驟然撲出。\n");
	set("bounty", ([
		"survive"         : 220,
		"unarmed mastery" : 50,
		"martial art"     : 34,
		"martial mastery" : 16,
		"combat"          : 22,
	]));
	setup();
}

// 奉陪到底、藉霧反撲（牠並不主動撲路人﹐由玩家 kill 起釁）。
int accept_fight(object ob)
{
	do_chat((: command, "say 霧狼幽綠的眼一沉﹐倏地隱沒進濃霧﹐下一瞬已自側面無聲撲出﹐獠牙森森﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
