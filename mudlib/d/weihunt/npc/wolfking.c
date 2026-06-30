// wolfking.c -- 灰背頭狼，盤踞衛國狼窩崖下、巨碩異常的塞狼之王，群狼之首。
//
// 結構沿用 /d/heifeng/npc/greywolf.c：可 kill、會還手、不主動攻擊路人(無 attitude)，
// 殺後只給 score(無錢)。戰力定在 level 36 一線——衛國邊塞獵場的最強對手、上段把關，
// 已是頗硬的猛物，須有相當火候的玩家方能應付。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("灰背頭狼", ({ "wolf king", "wolfking", "grey wolf king", "wolf", "huibeitoulang" }) );
	// 根骨 50 → 形體上限約 250 點；另以 advance_stat 大幅加厚氣血﹐群狼之王極耐戰。
	set_attr("con", 50);
	set_attr("str", 44);
	set_attr("dex", 30);
	set_race("human");
	set_class("commoner");
	set_level(36);

	// 撕咬剛猛絕倫、拆招閃躲俱精、內力深厚（閱盡塞外殺伐的群狼之王）。
	set_skill("unarmed", 64);
	set_skill("dodge", 36);
	set_skill("parry", 40);
	set_skill("force", 36);

	// 大幅厚其氣血﹐使之極耐打、有來有往（量重於黑風蒼狼﹐邊塞獵場上段把關）。
	advance_stat("kee", 72);

	set("age", 9);
	set("gender", "male");
	set("long",
		"一頭巨碩異常的灰背頭狼﹐比尋常塞狼壯出一倍﹐肩高及人胸﹐脊\n"
		"背一道銀灰的鬃毛根根賁張如戟。牠是這群塞狼的王﹐一雙黃眼閱\n"
		"盡了塞外的風霜殺伐﹐沉靜陰冷得不似走獸。牠伏在崖根狼窩的最\n"
		"深處﹐昂首一嗥﹐悠長淒厲﹐崖壁間迴聲不絕﹐群狼隨之齊聲應和。\n"
		"那一身的筋肉與牙爪﹐每一處都透著久經圍獵廝殺的剽悍與凶威。\n");
	// 純 score：江湖歷練(升級)、拳腳精熟、武術造詣、武學之道、實戰經驗。無錢幣。
	set("bounty", ([
		"survive"         : 620,
		"unarmed mastery" : 150,
		"martial art"     : 100,
		"martial mastery" : 50,
		"combat"          : 52,
	]));
	setup();
}

// 不主動撲路人﹐由玩家 kill 起釁；凶威畢露反撲。
int accept_fight(object ob)
{
	do_chat((: command, "say 灰背頭狼昂首發出一聲悠長淒厲的長嗥﹐群狼齊聲應和﹐牠脊毛賁張﹐挾著一身凶威疾撲而上﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
