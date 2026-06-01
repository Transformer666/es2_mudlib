// graywolf.c -- 灰狼，狼徑深處成群出沒的野狼，狼窩谷獵場最淺一級的獵物。
//
// 結構沿用 /d/wuling/npc/direwolf.c（承 /d/hudao/wild/npc/madwolf.c → rabbit.c）：
// 可 kill、會還手、不主動攻擊路人(無 attitude，由玩家 kill 起釁)，殺後只給
// score(無錢)。戰力定在 level 14 一線——接續武陵狼患的獨眼惡狼(lvl12)往上一級，
// 是備妥兵刃、稍有火候的玩家堂堂正正打得過的對手(狼窩谷獵場的入門級)。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("灰狼", ({ "grey wolf", "graywolf", "wolf", "huilang" }) );
	// 根骨 20 → 形體上限約 100 點，較獨眼惡狼(con18)略硬，群狼成隊、撕咬迅捷。
	set_attr("con", 20);
	set_attr("str", 18);
	set_attr("dex", 18);
	set_race("human");
	set_class("commoner");
	set_level(14);

	// 撕咬成群、身手矯捷，略諳閃拆，內力中平：是一場公平而有來有往的惡鬥。
	set_skill("unarmed", 22);
	set_skill("dodge", 18);
	set_skill("parry", 16);
	set_skill("force", 16);

	set("age", 3);
	set("gender", "male");
	set("long",
		"一頭瘦長精悍的灰狼﹐毛色灰中透黃﹐脊背一道深褐的鬃線直貫\n"
		"尾根。牠口吻尖長﹐齒列森森﹐齒間還沾著暗褐的舊血﹐慣於成\n"
		"群結隊地在這深山的亂石坡上奔突圍獵。此刻牠弓著脊背﹐喉間\n"
		"滾出一串低沉而急促的咯咯聲﹐一雙黃綠的眼睛死死盯住了你﹐\n"
		"後腿微屈﹐隨時要竄上來撕咬。\n");
	// 純 score：江湖歷練(升級)、拳腳精熟、武術造詣、實戰經驗。無錢幣、無 carry_money。
	set("bounty", ([
		"survive"         : 130,
		"unarmed mastery" : 34,
		"martial art"     : 24,
		"combat"          : 16,
	]));
	setup();
}

// 奉陪到底、凶悍反擊（牠並不主動撲路人﹐由玩家 kill 起釁）。
int accept_fight(object ob)
{
	do_chat((: command, "say 灰狼喉間滾出一串淒厲的咯咯聲﹐弓背豎鬃﹐獠牙森森地竄了上來﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
