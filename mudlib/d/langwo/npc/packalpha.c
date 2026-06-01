// packalpha.c -- 狼群頭狼，狼群嘯穴中統領群狼的領首之狼，凶悍善戰，極難纏。
//
// 結構沿用 /d/wuling/npc/direwolf.c（承 /d/hudao/wild/npc/madwolf.c → rabbit.c）：
// 可 kill、會還手、不主動攻擊路人(無 attitude)，殺後只給 score(無錢)。戰力定在
// level 32 一線——較青狼(26)更猛，乃嘯穴狼群之統領，是須有相當火候、持械方好
// 應付的勁敵(僅次於鐵背蒼狼與狼王)。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("狼群頭狼", ({ "pack alpha", "packalpha", "alpha", "wolf", "toulang" }) );
	set("nickname", "頭狼");
	// 根骨 48 → 形體上限約 240 點；另以 advance_stat 大幅加厚氣血，皮堅肉厚、極耐戰。
	set_attr("con", 48);
	set_attr("str", 42);
	set_attr("dex", 30);
	set_race("human");
	set_class("commoner");
	set_level(32);

	// 統領群狼、身經百戰：徒手已近高手之境，拆招、內力俱強。
	set_skill("unarmed", 64);
	set_skill("dodge", 40);
	set_skill("parry", 42);
	set_skill("force", 48);

	// 厚其氣血，使之耐打、有來有往（量輕於鐵背蒼狼，更輕於狼王）。
	advance_stat("kee", 120);

	set("age", 7);
	set("gender", "male");
	set("long",
		"一頭格外雄健的領首頭狼﹐較尋常野狼大上一圈﹐周身灰青的毛\n"
		"根根倒豎﹐肩胛厚實﹐筋肉虯結。牠是這嘯穴狼群的統領﹐昂首\n"
		"踞於群狼之中﹐一聲嗥起﹐十數頭野狼便齊聲相和。牠身經百\n"
		"戰﹐撲擊起來剛猛而有章法﹐連成群的青狼都對牠俯首帖耳。此\n"
		"刻牠虎視眈眈地盯住了你﹐喉間滾出一聲悠長而威嚴的低嗥﹐尾\n"
		"梢沉沉地拍打著地面。\n");
	// 純 score：江湖歷練(升級)、拳腳精熟、武術造詣、武學之道、實戰經驗。無錢幣。
	set("bounty", ([
		"survive"         : 580,
		"unarmed mastery" : 130,
		"martial art"     : 88,
		"martial mastery" : 52,
		"combat"          : 52,
	]));
	setup();
}

// 奉陪到底、凶悍反擊（牠並不主動撲路人﹐由玩家 kill 起釁）。
int accept_fight(object ob)
{
	do_chat((: command, "say 狼群頭狼一聲威嚴的長嗥﹐群狼齊聲相和﹐牠巨軀一縱﹐剛猛地撲向膽敢犯境的來人﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
