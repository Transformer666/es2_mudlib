// blackbear.c -- 黑熊，熊月村後山林徑一帶覓食盤桓的山熊，後山獵場入門級獵物。
//
// 結構沿用 /d/heifeng/npc/greywolf.c(承 madwolf→rabbit)：可 kill、會還手、不主動
// 攻擊路人(無 attitude，由玩家 kill 起釁)，殺後只給 score(無錢)。戰力定在 level
// 28——任務交付獵場下限 25-40 之入門級，力大皮厚、耐打的山熊。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("黑熊", ({ "black bear", "blackbear", "bear", "heixiong" }) );
	// 根骨 42 → 形體上限厚實；另以 advance_stat 加厚氣血，皮糙肉厚、力大耐戰。
	set_attr("con", 42);
	set_attr("str", 40);
	set_attr("dex", 22);
	set_race("human");
	set_class("commoner");
	set_level(28);

	// 熊掌拍擊剛猛、皮厚耐打、身手卻拙：徒手力沉，閃拆中平，內力平平。
	set_skill("unarmed", 46);
	set_skill("dodge", 24);
	set_skill("parry", 30);
	set_skill("force", 26);

	// 厚其氣血，使之耐打、有來有往(參 greywolf advance_stat 之法，量略重之)。
	advance_stat("kee", 50);

	set("age", 8);
	set("gender", "male");
	set("long",
		"一頭體格壯碩的黑熊﹐毛色烏黑油亮﹐胸前一抹月牙似的白斑在\n"
		"昏光裡格外醒目。牠四肢粗壯如柱﹐一雙熊掌寬厚有力﹐掌底的利\n"
		"爪足有寸許長﹐村口那幾株老樹上深及寸的爪痕﹐便是這般物事留\n"
		"下的。此刻牠正埋頭翻撿腐木下的蟲蟻﹐見了生人也不甚驚惶﹐只\n"
		"緩緩直起半人多高的身軀﹐咻咻地嗅著﹐一雙小眼睛裡透著山獸的\n"
		"兇蠻﹐喉間滾出一聲沉悶的低吼。\n");
	// 純 score：江湖歷練(升級)、拳腳精熟、武術造詣、實戰經驗。無錢幣。
	set("bounty", ([
		"survive"         : 420,
		"unarmed mastery" : 96,
		"martial art"     : 64,
		"martial mastery" : 32,
		"combat"          : 34,
	]));
	setup();
}

// 奉陪到底、剛猛反擊(牠並不主動撲路人﹐由玩家 kill 起釁)。
int accept_fight(object ob)
{
	do_chat((: command, "say 黑熊霍地直起壯碩的身軀﹐張開血盆大口發出一聲震林的怒吼﹐揮起寬厚的熊掌猛撲過來﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
