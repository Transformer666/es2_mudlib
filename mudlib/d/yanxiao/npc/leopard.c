// leopard.c -- 莽林斑豹，林深處盤踞的猛獸，較山狸更兇、更難纏。
//
// 結構沿用 /d/heifeng/npc/greywolf.c：可 kill、會還手、不主動攻擊路人(無
// attitude，由玩家 kill 起釁)，殺後只給 score(無錢)。戰力定在 level 26 一
// 線——較山狸(20)更硬，已諳吐納內力，是莽林獵場的中段對手。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("斑豹", ({ "leopard", "banbao", "panther" }) );
	set("nickname", "斑豹");
	// 根骨 38 → 形體上限約 190 點；另以 advance_stat 加厚氣血，皮韌肉緊、耐戰。
	set_attr("con", 38);
	set_attr("str", 36);
	set_attr("dex", 34);
	set_race("human");
	set_class("commoner");
	set_level(26);

	// 撲擊剛猛、身法迅捷、略諳吐納：徒手、閃躲、拆招俱佳，內力中平。
	set_skill("unarmed", 46);
	set_skill("dodge", 38);
	set_skill("parry", 30);
	set_skill("force", 26);

	// 厚其氣血，使之耐打、有來有往（參 greywolf advance_stat 之法）。
	advance_stat("kee", 38);

	set("age", 5);
	set("gender", "male");
	set("long",
		"一頭體態雄健的莽林斑豹﹐金黃的皮毛上綴滿了一團團墨色的銅\n"
		"錢花斑﹐在幽綠的林光下隱隱泛著油亮的光。牠四肢修長而充滿\n"
		"爆發的力道﹐踏在倒木腐葉上竟悄無聲息﹐是這片林深處最善伏\n"
		"擊的猛物。此刻牠壓低了身子﹐尾尖微微抽動﹐喉間滾出一聲低\n"
		"沉的悶吼﹐金綠的眼睛裡迸出兇光﹐後腿一蹬﹐便要疾撲而上。\n");
	// 純 score：江湖歷練(升級)、拳腳精熟、武術造詣、武學之道、實戰經驗。無錢幣。
	set("bounty", ([
		"survive"         : 360,
		"unarmed mastery" : 86,
		"martial art"     : 56,
		"martial mastery" : 28,
		"combat"          : 30,
	]));
	setup();
}

// 奉陪到底、凶悍反擊（牠並不主動撲路人﹐由玩家 kill 起釁）。
int accept_fight(object ob)
{
	do_chat((: command, "say 斑豹壓低身子﹐喉間滾出一聲悶吼﹐尾尖一抽﹐如一道金影疾撲而上﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
