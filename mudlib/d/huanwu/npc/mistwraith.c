// mistwraith.c -- 迷霧鬼魅，幻霧森林林心盤踞的枯槁厲魂，獵場巔峰之獵物。
//
// 結構沿用 /d/langwo/npc/graywolf.c → wolfking.c 之巔峰獸路數：可 kill、會還手、
// 不主動攻擊路人(無 attitude)，殺後只給 score(無錢)。戰力定在 level 29 一線
// （docs 任務要求 lv 28-30 上限）——是雪亭→李家→幻霧 新手村群獵場學習曲線的
// 終點對手，較澗谷霧魅(lvl24)更厲、更難纏。設定上是困死林心、怨念最深的厲魂，
// 機制上仍走尋常 humanoid 戰鬥（不臆造特殊鬼怪/掉寶機制——僅作氛圍與獵場頂點）。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("迷霧鬼魅", ({ "mist wraith", "mistwraith", "wraith", "guimei" }) );
	// 根骨 42 → 形體上限約 210 點；另以 advance_stat 厚其氣血，怨念深重、極耐戰。
	set_attr("con", 42);
	set_attr("str", 34);
	set_attr("dex", 36);
	set_race("human");
	set_class("commoner");
	set_level(29);

	// 困林日久、霧氣淬煉：閃拆抓拿俱臻純熟，內力已厚——是新手獵場最硬的一關。
	set_skill("unarmed", 56);
	set_skill("dodge", 44);
	set_skill("parry", 40);
	set_skill("force", 38);

	// 厚其氣血，使之耐打、有來有往（量參狼窩谷蒼狼王 advance_stat 之法，略輕）。
	advance_stat("kee", 48);

	set("age", 60);
	set("gender", "male");
	set("long",
		"一道比尋常霧魅更濃、更厲的鬼魅之影盤踞在霧靈古樹下﹐通體\n"
		"灰白如骨﹐約略是個極瘦的人形﹐枯槁的十指卻長著利爪一般的\n"
		"指甲。它周身的青幽冷光濃得幾乎凝成實質﹐所過之處﹐連那彌\n"
		"天的白霧都翻湧不安。村人說﹐這是當年最早迷失在幻霧森林、\n"
		"困死林心、怨念積得最深的一縷厲魂﹐世世代代盤踞在這禁地之\n"
		"中﹐連別的鬼魅都對它俯首。它那雙空洞的眼眶死死綴住你﹐喉\n"
		"間滾出一聲悠長而怨毒的厲嘯﹐聽得人魂飛魄散——非藝高膽壯、\n"
		"持械有備者﹐萬莫與它為敵。\n");
	// 純 score：江湖歷練(升級)、拳腳精熟、武術造詣、武學之道、實戰經驗。無錢幣。
	set("bounty", ([
		"survive"         : 460,
		"unarmed mastery" : 100,
		"martial art"     : 66,
		"martial mastery" : 34,
		"combat"          : 36,
	]));
	setup();
}

// 奉陪到底、怨毒反撲（它並不主動撲路人﹐由玩家 kill 起釁）。
int accept_fight(object ob)
{
	do_chat((: command, "say 迷霧鬼魅厲嘯一聲﹐枯爪箕張﹐周身青光暴漲﹐裹著翻湧的白霧疾撲而上﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
