// wildboar.c -- 霧林野豬，幻霧森林林緣淺處拱食的兇悍野豬，獵場入門級獵物。
//
// 結構沿用 /d/langwo/npc/graywolf.c（承 direwolf → madwolf → rabbit）：可 kill、
// 會還手、不主動攻擊路人(無 attitude，由玩家 kill 起釁)，殺後只給 score(無錢)。
// 戰力定在 level 16 一線——是雪亭→李家→幻霧 新手村群獵場學習曲線的入門對手，
// 略強於武陵狼患的獨眼惡狼(lvl12)、狼窩谷灰狼(lvl14)，備妥兵刃便堂堂打得過。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("霧林野豬", ({ "wild boar", "wildboar", "boar", "yezhu" }) );
	// 根骨 24 → 形體上限約 120 點，皮糙肉厚、低頭橫衝直撞，耐打而少巧勁。
	set_attr("con", 24);
	set_attr("str", 22);
	set_attr("dex", 14);
	set_race("human");
	set_class("commoner");
	set_level(16);

	// 獠牙衝撞剛猛、身手笨拙：徒手攻擊尚可，閃拆平平，內力低微。
	set_skill("unarmed", 24);
	set_skill("dodge", 14);
	set_skill("parry", 16);
	set_skill("force", 12);

	set("age", 4);
	set("gender", "male");
	set("long",
		"一頭脊背烏黑、鬃毛倒豎的霧林野豬﹐生得膘肥體壯﹐兩枚焦黃\n"
		"的獠牙自嘴角彎彎地翹出來﹐磨得鋒利。牠在幻霧森林的林緣淺\n"
		"處拱食慣了﹐皮糙肉厚﹐脾性卻極暴﹐一雙小眼睛在白霧裡泛著\n"
		"赤紅﹐受了驚便低頭翹尾、沒命地橫衝直撞﹐尋常獵戶見了也要\n"
		"退避三分。\n");
	// 純 score：江湖歷練(升級)、拳腳精熟、武術造詣、實戰經驗。無錢幣、無 carry_money。
	set("bounty", ([
		"survive"         : 160,
		"unarmed mastery" : 38,
		"martial art"     : 26,
		"combat"          : 18,
	]));
	setup();
}

// 奉陪到底、暴起反擊（牠並不主動撲路人﹐由玩家 kill 起釁）。
int accept_fight(object ob)
{
	do_chat((: command, "say 霧林野豬受驚似地嗷叫一聲﹐低頭翹尾﹐獠牙森森地直撞過來﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
