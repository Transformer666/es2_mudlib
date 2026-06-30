// otter.c -- 水獺，婁縣水澤蘆蕩裡溜滑迅捷的捕魚水獺，護食回身撕咬。
//
// 結構沿用 /d/heifeng/npc/greywolf.c：可 kill、會還手、不主動攻擊路人(無 attitude)，
// 殺後只給 score(無錢)。戰力定在 level 20 一線——較蘆雁(14)更硬，是婁縣獵場的中段對手。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("水獺", ({ "river otter", "otter", "shuita" }) );
	// 根骨 34 → 形體上限約 170 點；另以 advance_stat 加厚氣血﹐水裡水裡耐戰。
	set_attr("con", 34);
	set_attr("str", 28);
	set_attr("dex", 32);
	set_race("human");
	set_class("commoner");
	set_level(20);

	// 游水捕魚快如游龍、閃竄極靈、撕咬利齒不鬆口﹐內力中平。
	set_skill("unarmed", 34);
	set_skill("dodge", 32);
	set_skill("parry", 22);
	set_skill("force", 16);

	// 厚其氣血﹐使之耐打、有來有往。
	advance_stat("kee", 28);

	set("age", 3);
	set("gender", "male");
	set("long",
		"一隻水澤裡的水獺﹐生得一身油亮的褐毛﹐圓頭短腿﹐拖著一條粗\n"
		"壯的尾巴﹐一雙圓溜溜的小眼透著機靈。牠游水捕魚快如游龍﹐在\n"
		"泥岸的窩穴間進進出出﹐叼著肥魚倏地鑽入水裡。這畜生看著憨態\n"
		"可掬﹐護起食、護起崽來卻凶得很﹐回身一口利齒咬住便死也不鬆\n"
		"口﹐溜滑得教人按捺不住。\n");
	// 純 score：江湖歷練(升級)、拳腳精熟、武術造詣、武學之道、實戰經驗。無錢幣。
	set("bounty", ([
		"survive"         : 240,
		"unarmed mastery" : 60,
		"martial art"     : 40,
		"martial mastery" : 20,
		"combat"          : 24,
	]));
	setup();
}

// 不主動撲路人﹐由玩家 kill 起釁；護食凶撲。
int accept_fight(object ob)
{
	do_chat((: command, "say 水獺嗤嗤地低吼一聲﹐圓眼一瞪﹐溜滑地竄上﹐回身一口利齒死死咬來﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
