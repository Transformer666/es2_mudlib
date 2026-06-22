// snowtianao.c -- 白睛天獒，雪窟群獒的領頭巨獒，天山獵場壓陣之獸。
//
// 結構沿用 /d/langwo/npc/ironwolf.c（承 azurewolf.c → rabbit.c）：可 kill、會
// 還手、不主動攻擊路人(無 attitude)，殺後只給 score(無錢)。戰力定在 level 62
// 一線——較尋常天獒(56)更巨更猛，是雪窟最深處盤踞冰臺的領頭巨獒，須有相當
// 火候、持械有備方好應付。本獵場壓陣之獸，雪窟單隻盤踞、可重生。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("白睛天獒", ({ "snow mastiff", "snowmastiff", "snowtianao", "mastiff", "tianao", "ao" }) );
	set("nickname", "雪窟之主");
	// 根骨 68 → 形體上限極厚；另以 advance_stat 大幅加厚氣血，皮堅毛密、極耐戰。
	set_attr("con", 68);
	set_attr("str", 60);
	set_attr("dex", 44);
	set_race("human");
	set_class("commoner");
	set_level(62);

	// 領頭巨獒撲擊勢沉力猛、目泛青白詭光：徒手已臻高手之境，閃躲、拆招、內力俱強。
	set_skill("unarmed", 150);
	set_skill("dodge", 72);
	set_skill("parry", 78);
	set_skill("force", 96);

	// 厚其氣血，使之耐打、有來有往（厚於尋常天獒的 kee+200，壓陣之獸故）。
	advance_stat("kee", 320);

	set("age", 11);
	set("gender", "male");
	set("long",
		"一頭格外巨碩的灰白天獒﹐肩高及人胸﹐周身覆著一層蓬鬆如雪\n"
		"的灰白長毛﹐毛梢凝著薄霜﹐立起來幾與壯漢比肩。牠是這雪窟\n"
		"群獒的領頭之獸﹐獨踞窟底的冰臺之上﹐連成群的天獒見了也要\n"
		"俯首退避。牠最教人膽寒的是那雙泛著詭異青白冷光的眼睛——\n"
		"獵戶間傳說凡被牠那白睛盯上的活物﹐縱奔逃千里亦難逃牠的爪\n"
		"牙。此刻牠脖頸低伏﹐喉間滾出一聲悠長陰沉的低嗥﹐震得滿窟\n"
		"的冰稜簌簌作響。\n");
	// 純 score：江湖歷練(升級)、拳腳精熟、武術造詣、武學之道、實戰經驗。無錢幣。
	set("bounty", ([
		"survive"         : 3200,
		"unarmed mastery" : 600,
		"martial art"     : 400,
		"martial mastery" : 240,
		"combat"          : 220,
	]));
	setup();
}

// 奉陪到底、凶悍反擊（牠並不主動撲路人﹐由玩家 kill 起釁）。
int accept_fight(object ob)
{
	do_chat((: command, "say 白睛天獒一聲震窟的長嗥﹐青白雙目精光暴漲﹐巨軀拔地撲向膽敢闖穴的來人﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
