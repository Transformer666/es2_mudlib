// greywolf.c -- 蒼狼，黑風山風嘯石澗一帶盤踞的巨狼，較山豺更猛、更難纏。
//
// 結構沿用 /d/hudao/wild/npc/madwolf.c（承 /d/snow/npc/rabbit.c）：可 kill、會
// 還手、不主動攻擊路人(無 attitude)，殺後只給 score(無錢)。戰力定在 level 26 一線
// ——較山豺(22)更硬，已諳吐納內力，是黑風山獵場的中段對手。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("蒼狼", ({ "grey wolf", "greywolf", "wolf", "canglang" }) );
	// 根骨 40 → 形體上限約 200 點；另以 advance_stat 加厚氣血，皮糙肉厚、耐戰。
	set_attr("con", 40);
	set_attr("str", 34);
	set_attr("dex", 24);
	set_race("human");
	set_class("commoner");
	set_level(26);

	// 撕咬剛猛、略諳吐納：徒手、拆招、閃躲俱佳，內力中平。
	set_skill("unarmed", 44);
	set_skill("dodge", 26);
	set_skill("parry", 28);
	set_skill("force", 24);

	// 厚其氣血，使之耐打、有來有往（參雪吟莊主魚鐵山 advance_stat 之法，量遠輕之）。
	advance_stat("kee", 40);

	set("age", 5);
	set("gender", "male");
	set("long",
		"一頭體格雄健的蒼灰巨狼﹐肩高及人腰﹐周身覆著一層粗硬如針\n"
		"的灰毛﹐風過處根根倒豎。牠是黑風山這片石澗的霸主﹐獨來獨\n"
		"往﹐連成群的山豺見了也要繞道而行。牠四爪穩穩踏在嶙峋的亂\n"
		"石上﹐脖頸低伏﹐喉間滾出一聲悠長而陰沉的低嗥﹐那聲音在風\n"
		"嘯的澗谷裡來回激盪﹐聽得人心頭發緊。\n");
	// 純 score：江湖歷練(升級)、拳腳精熟、武術造詣、武學之道、實戰經驗。無錢幣。
	set("bounty", ([
		"survive"         : 380,
		"unarmed mastery" : 90,
		"martial art"     : 60,
		"martial mastery" : 30,
		"combat"          : 32,
	]));
	setup();
}

// 奉陪到底、凶悍反擊（牠並不主動撲路人﹐由玩家 kill 起釁）。
int accept_fight(object ob)
{
	do_chat((: command, "say 蒼狼脖頸一沉﹐發出一聲悠長陰沉的低嗥﹐弓身豎毛﹐疾撲而上﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
