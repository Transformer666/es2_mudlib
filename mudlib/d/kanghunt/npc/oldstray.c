// oldstray.c -- 老野狗，盤踞康平亂葦深處、體格壯碩的塘窪老野狗，群狗之首。
//
// 結構沿用 /d/heifeng/npc/greywolf.c：可 kill、會還手、不主動攻擊路人(無 attitude)，
// 殺後只給 score(無錢)。戰力定在 level 22 一線——是康平獵場的最強對手、上段把關。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("老野狗", ({ "old stray", "oldstray", "stray dog", "dog", "laoyegou" }) );
	// 根骨 32 → 形體上限約 160 點；另以 advance_stat 加厚氣血，瘸腿卻更耐戰。
	set_attr("con", 32);
	set_attr("str", 30);
	set_attr("dex", 22);
	set_race("human");
	set_class("commoner");
	set_level(22);

	// 撕咬剛猛、拆招閃躲俱熟、內力中平（老於江湖的塘窪霸主）。
	set_skill("unarmed", 38);
	set_skill("dodge", 24);
	set_skill("parry", 26);
	set_skill("force", 18);

	// 厚其氣血﹐使之耐打、有來有往（量遠輕於黑風蒼狼）。
	advance_stat("kee", 28);

	set("age", 7);
	set("gender", "male");
	set("long",
		"一條毛色斑駁的老野狗﹐體格比尋常野狗壯出一圈﹐右後腿瘸了﹐\n"
		"走起來一拐一拐﹐凶悍卻不減反增。牠周身的黃毛糾結著塘泥血痂﹐\n"
		"一張臉橫七豎八地佈滿撕咬的舊疤﹐一雙黃眼陰沉沉地盯著生人。\n"
		"這片亂葦裡的野狗都聽牠調遣﹐牠便是這荒塘窪地不折不扣的霸主﹐\n"
		"喉間那聲悠長的低吼﹐連覓食的田鼠聽了也要噤聲伏低。\n");
	// 純 score：江湖歷練(升級)、拳腳精熟、武術造詣、武學之道、實戰經驗。無錢幣。
	set("bounty", ([
		"survive"         : 280,
		"unarmed mastery" : 70,
		"martial art"     : 46,
		"martial mastery" : 24,
		"combat"          : 26,
	]));
	setup();
}

// 不主動撲路人﹐由玩家 kill 起釁；凶悍反撲。
int accept_fight(object ob)
{
	do_chat((: command, "say 老野狗弓身豎毛﹐發出一聲悠長陰沉的低吼﹐瘸著腿疾撲而上﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
