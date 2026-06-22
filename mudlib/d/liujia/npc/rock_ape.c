// rock_ape.c -- 巖猿，六甲山腰絕壁密林間攀崖踏壁的山猿，六甲山獵場中段的獵物。
//
// 結構沿用 /d/heifeng/npc/leopard.c（承 /d/hudao/wild/npc/madwolf.c → rabbit.c）：
// 可 kill、會還手、不主動攻擊路人(無 attitude，由玩家 kill 起釁)，殺後只給
// score(無錢)。戰力定在 level 38 一線——較山豕(32)更猛，身手矯捷、力大臂長，是
// 六甲山獵場中段、須有相當火候方好應付的對手。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("巖猿", ({ "rock ape", "ape", "yanyuan" }) );
	// 根骨 52 → 形體上限約 260 點；臂長力沉、攀崖踏壁，極耐戰。
	set_attr("con", 52);
	set_attr("str", 46);
	set_attr("dex", 38);
	set_race("human");
	set_class("commoner");
	set_level(38);

	// 拳掌摜擊、攀縱迅捷：徒手已近高手之境，閃躲、拆招俱高，內力中上。
	set_skill("unarmed", 96);
	set_skill("dodge", 56);
	set_skill("parry", 50);
	set_skill("force", 48);

	// 厚其氣血，使之耐打、有來有往（量介於黑風山斑斕虎 lvl36 的 150 與虎王之間）。
	advance_stat("kee", 170);

	set("age", 12);
	set("gender", "male");
	set("long",
		"一頭軀幹魁偉的巖猿﹐周身覆著一層青灰色的長毛﹐與這六甲山\n"
		"的青黑岩壁渾然一色。牠兩臂奇長﹐幾乎垂及膝下﹐臂上虬筋盤\n"
		"結﹐臂力之沉﹐能生生扳折碗口粗的松枝。牠是攀崖踏壁的好\n"
		"手﹐縱躍於絕壁石稜之間迅捷如飛﹐尋常獵戶莫說近身﹐便是遠\n"
		"遠望見牠的身影也要心驚。此刻牠齜著牙﹐捶著胸膛﹐喉間滾出\n"
		"一串低沉的吼聲﹐一雙赤紅的眼睛死死盯住了你。\n");
	// 純 score：江湖歷練(升級)、拳腳精熟、武術造詣、武學之道、實戰經驗。無錢幣。
	set("bounty", ([
		"survive"         : 800,
		"unarmed mastery" : 170,
		"martial art"     : 118,
		"martial mastery" : 70,
		"combat"          : 64,
	]));
	setup();
}

// 奉陪到底、凶悍反擊（牠並不主動撲路人﹐由玩家 kill 起釁）。
int accept_fight(object ob)
{
	do_chat((: command, "say 巖猿捶著胸膛長嘯一聲﹐倏地縱身撲下﹐長臂摜起一掌挾風劈來﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
