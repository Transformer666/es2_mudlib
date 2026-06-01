// tiger.c -- 斑斕虎，黑風山虎嘯幽谷中盤踞的猛虎，山中群獸之雄，極難纏。
//
// 結構沿用 /d/hudao/wild/npc/madwolf.c（承 /d/snow/npc/rabbit.c）：可 kill、會
// 還手、不主動攻擊路人(無 attitude)，殺後只給 score(無錢)。戰力定在 level 36 一線
// ——黑風山獵場最深處之外的大物，僅次於虎王，是須有相當火候、持械方好應付的勁敵。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("斑斕虎", ({ "striped tiger", "tiger", "banlan hu" }) );
	set("nickname", "山君");
	// 根骨 56 → 形體上限約 280 點；另以 advance_stat 大幅加厚氣血，皮堅肉厚、極耐戰。
	set_attr("con", 56);
	set_attr("str", 48);
	set_attr("dex", 32);
	set_race("human");
	set_class("commoner");
	set_level(36);

	// 虎掌拍擊勢大力沉、爪牙俱利：徒手已近高手之境，拆招、內力俱強。
	set_skill("unarmed", 90);
	set_skill("dodge", 48);
	set_skill("parry", 52);
	set_skill("force", 60);

	// 厚其氣血，使之耐打、有來有往（仍輕於魚鐵山 lvl40 的 250、摩雲 lvl50 的 400）。
	advance_stat("kee", 150);

	set("age", 8);
	set("gender", "male");
	set("long",
		"一頭吊睛白額的斑斕猛虎﹐立起來幾與小馬等高﹐周身金黃的皮\n"
		"毛上墨色的斑紋如焰似浪﹐額心一個天然的「王」字隱隱可辨。\n"
		"牠是這黑風山幽谷的山君﹐一聲長嘯能震得滿谷松濤翻湧、群獸\n"
		"匍匐。牠虎目如炬﹐睥睨之間自有一股不怒而威的兇煞之氣﹐巨\n"
		"掌寬若蒲扇﹐利爪森然﹐尾梢沉沉地拍打著地面﹐每一下都濺起\n"
		"一蓬塵土。尋常獵戶莫說獵牠﹐便是遠遠望見牠的身影﹐也要嚇\n"
		"得魂飛魄散。\n");
	// 純 score：江湖歷練(升級)、拳腳精熟、武術造詣、武學之道、實戰經驗。無錢幣。
	set("bounty", ([
		"survive"         : 760,
		"unarmed mastery" : 160,
		"martial art"     : 110,
		"martial mastery" : 64,
		"combat"          : 60,
	]));
	setup();
}

// 奉陪到底、凶悍反擊（牠並不主動撲路人﹐由玩家 kill 起釁）。
int accept_fight(object ob)
{
	do_chat((: command, "say 斑斕虎一聲震天的長嘯﹐滿谷松濤翻湧﹐巨軀拔地撲向膽敢犯境的來人﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
