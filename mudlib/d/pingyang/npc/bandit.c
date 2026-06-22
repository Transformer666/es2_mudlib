// bandit.c -- 山賊嘍囉，平陽山道與半山一帶據道劫掠的山賊，平陽山獵場的中段獵物。
//
// 結構沿用 /d/heifeng/npc/greywolf.c（承 rabbit.c）：可 kill、會還手、不主動攻擊路人
// (無 attitude，由玩家 kill 起釁)，殺後給 score 與少量散碎銀錢(山賊劫掠所得)。戰力定在
// level 42 一線——承黑風山蒼狼(lvl26)、狼窩谷狼王(lvl40)往上一級，是備妥兵刃、有相當火候
// 的玩家堂堂正正打得過的對手(平陽山獵場的中段)。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("山賊", ({ "bandit", "mountain bandit", "shanzei" }) );
	// 根骨 44 → 形體上限約 220 點；另以 advance_stat 略加厚氣血，皮糙肉厚、耐打。
	set_attr("con", 44);
	set_attr("str", 38);
	set_attr("dex", 30);
	set_race("human");
	set_class("commoner");
	set_level(42);

	// 山賊久經廝殺、慣使朴刀(blade)，拆招閃躲俱有些火候，內力中平：是一場有來有往的惡鬥。
	set_skill("blade", 60);
	set_skill("unarmed", 40);
	set_skill("dodge", 36);
	set_skill("parry", 40);
	set_skill("force", 36);

	// 略厚其氣血，使之耐打、有來有往（量遠輕於 boss 與雪吟莊主一系）。
	advance_stat("kee", 60);

	set("age", 31);
	set("gender", "male");
	set("long",
		"一個衣衫襤褸、面相兇橫的山賊嘍囉。他臉上橫著一道刀疤﹐一\n"
		"雙三角眼滴溜溜地亂轉﹐腰間胡亂挎著一柄缺了口的朴刀。這夥山\n"
		"賊原是平陽山附近的流民潑皮﹐被那寨主公孫一笑收攏聚作一夥﹐\n"
		"據山為患﹐專一在這山道上攔劫過往的客商行旅。他此刻齜牙咧嘴\n"
		"地盯住了你﹐手已按上刀柄﹐口裡吆喝著要你留下買路錢。\n");
	// 山賊劫掠為生，殺之給 score 並掉落少量散碎銀錢（不義之財）。
	set("bounty", ([
		"survive"       : 560,
		"blade mastery"  : 120,
		"martial art"    : 80,
		"martial mastery": 45,
		"combat"         : 45,
	]));
	setup();
	// 山賊劫掠所得的散碎銀錢（殺後可自屍身取得，量少）。
	carry_money("silver", 3);
}

// 奉陪到底、兇悍反擊（牠並不主動撲路人﹐由玩家 kill 起釁）。
int accept_fight(object ob)
{
	do_chat((: command, "say 山賊獰笑一聲﹐拔出朴刀﹕識相的留下買路錢﹐不然休怪爺爺的刀不長眼﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
