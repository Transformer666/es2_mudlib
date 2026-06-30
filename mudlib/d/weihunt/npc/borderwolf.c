// borderwolf.c -- 塞狼，盤踞衛國邊塞、成群圍獵的灰背塞外巨狼。
//
// 結構沿用 /d/heifeng/npc/greywolf.c：可 kill、會還手、不主動攻擊路人(無 attitude)，
// 殺後只給 score(無錢)。戰力定在 level 28 一線——較沙狐(24)更硬，是衛國獵場的中段對手。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("塞狼", ({ "border wolf", "borderwolf", "wolf", "sailang" }) );
	// 根骨 42 → 形體上限約 210 點；另以 advance_stat 加厚氣血﹐塞外巨狼皮糙肉厚。
	set_attr("con", 42);
	set_attr("str", 36);
	set_attr("dex", 26);
	set_race("human");
	set_class("commoner");
	set_level(28);

	// 撕咬剛猛、閃躲拆招俱熟、略諳吐納﹐塞外苦寒磨出的硬骨頭。
	set_skill("unarmed", 48);
	set_skill("dodge", 28);
	set_skill("parry", 30);
	set_skill("force", 26);

	// 厚其氣血﹐使之耐打、有來有往。
	advance_stat("kee", 44);

	set("age", 5);
	set("gender", "male");
	set("long",
		"一頭塞外的灰背巨狼﹐肩高及人腰﹐周身覆著一層粗硬如針的灰毛﹐\n"
		"塞風一吹根根倒豎。塞外苦寒﹐磨出牠一身的硬骨頭與凶性﹐四爪\n"
		"穩穩踏在亂石上﹐脖頸低伏﹐一雙黃眼閃著饑寒的冷光。牠慣與同\n"
		"群圍獵﹐連失蹄的牛馬也敢撲咬﹐喉間滾出的低嗥裡透著塞外的肅\n"
		"殺﹐是這片邊塞荒坡上不折不扣的猛物。\n");
	// 純 score：江湖歷練(升級)、拳腳精熟、武術造詣、武學之道、實戰經驗。無錢幣。
	set("bounty", ([
		"survive"         : 420,
		"unarmed mastery" : 100,
		"martial art"     : 66,
		"martial mastery" : 32,
		"combat"          : 36,
	]));
	setup();
}

// 不主動撲路人﹐由玩家 kill 起釁；凶悍反撲。
int accept_fight(object ob)
{
	do_chat((: command, "say 塞狼脖頸一沉﹐發出一聲悠長陰沉的低嗥﹐弓身豎毛﹐疾撲而上﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
