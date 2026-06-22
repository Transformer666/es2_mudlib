// cinnabarape.c -- 赭背靈猿，秋一谷霜林深處守藥的巨猿，力沉勢猛、通幾分靈性。
//
// 結構沿用 /d/langwo/npc/ironwolf.c（承 azurewolf → greywolf → rabbit）：可 kill、
// 會還手、不主動攻擊路人(無 attitude)，殺後只給 score(無錢)。戰力定在 level 48
// 一線——秋一谷霜林深處的較高階靈獸，較藥圃靈狐(42)更硬，是直逼谷底前的硬仗。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("赭背靈猿", ({ "cinnabar ape", "cinnabarape", "ape", "zhebei lingyuan" }) );
	set("nickname", "守林之猿");
	// 根骨 56 → 形體上限約 280 點；另以 advance_stat 大幅加厚氣血，力沉血厚、極耐戰。
	set_attr("con", 56);
	set_attr("str", 50);
	set_attr("dex", 34);
	set_race("human");
	set_class("commoner");
	set_level(48);

	// 守林巨猿：膂力剛猛、長臂撲擊勢沉力大，拆招、內力俱臻不弱之境。
	set_skill("unarmed", 96);
	set_skill("dodge", 52);
	set_skill("parry", 66);
	set_skill("force", 70);

	// 大幅厚其氣血（kee+180），使之血厚耐戰（量輕於谷底守谷者靈樞藥叟）。
	advance_stat("kee", 180);

	set("age", 11);
	set("gender", "male");
	set("long",
		"一頭赭褐色的巨猿﹐膀闊腰圓﹐臂長過膝﹐立起來幾與壯漢比\n"
		"肩。牠周身覆著一層赭褐色的長毛﹐毛間沾著點點霜白﹐脊背\n"
		"一道毛色尤深﹐赭紅如染了硃砂。牠一雙深陷的眼睛精芒湛\n"
		"湛﹐竟似頗通靈性——久居這秋一谷霜林深處﹐吸納了谷中醇厚\n"
		"的藥石靈氣﹐這巨猿便成了林中靈草奇石的看守。此刻牠捶著\n"
		"胸膛﹐喉間滾出一聲聲低沉如雷的警嗥﹐齜出滿口森白的利\n"
		"齒﹐那股沉雄的兇威壓得人幾乎喘不過氣。\n");
	set("chat_chance_combat", 2);
	set("chat_msg_combat", ({
		"赭背靈猿暴吼一聲﹐雙臂如鐵錘般當頭砸落﹐震得滿林霜雪簌簌而墜。\n",
		"赭背靈猿長臂一探﹐自虯枝間盪將過來﹐挾著一股沉雄的勁風橫掃而至。\n",
	}));
	// 純 score：江湖歷練(升級)、拳腳精熟、武術造詣、武學之道、實戰經驗、武名。無錢幣。
	set("bounty", ([
		"survive"         : 760,
		"unarmed mastery" : 170,
		"martial art"     : 120,
		"martial mastery" : 70,
		"combat"          : 70,
		"martial fame"    : 40,
	]));
	setup();
}

// 奉陪到底、凶悍反擊（牠並不主動撲路人﹐由玩家 kill 起釁）。
int accept_fight(object ob)
{
	do_chat((: command, "say 赭背靈猿暴吼一聲﹐捶胸頓足﹐挾著滔天的沉雄兇威自虯枝間撲擊而下﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
