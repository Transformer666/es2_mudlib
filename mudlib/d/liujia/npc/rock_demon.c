// rock_demon.c -- 巖魈，六甲洞中盤踞、吸納山中精氣的山精，六甲山獵場深處的勁敵。
//
// 結構沿用 /d/heifeng/npc/tiger.c（承 /d/hudao/wild/npc/madwolf.c → rabbit.c）：
// 可 kill、會還手、不主動攻擊路人(無 attitude，由玩家 kill 起釁)，殺後只給
// score(無錢)。戰力定在 level 44 一線——較巖猿(38)更兇，已通靈性、內力深厚，是
// 六甲山獵場深處、僅次於峰頂散仙的大物，須有相當火候、持械方好應付。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("巖魈", ({ "rock demon", "demon", "yanxiao" }) );
	set("nickname", "六甲山精");
	// 根骨 60 → 形體上限約 300 點；另以 advance_stat 大幅加厚氣血，皮堅肉厚、極耐戰。
	set_attr("con", 60);
	set_attr("str", 52);
	set_attr("dex", 36);
	set_race("human");
	set_class("commoner");
	set_level(44);

	// 通了靈性、諳了吐納：徒手剛猛、拆招閃躲俱強，內力已厚。
	set_skill("unarmed", 110);
	set_skill("dodge", 60);
	set_skill("parry", 64);
	set_skill("force", 80);

	// 厚其氣血，使之耐打、有來有往（量介於黑風山斑斕虎 lvl36 的 150 與摩雲 lvl50 的 400 之間）。
	advance_stat("kee", 230);

	set("age", 30);
	set("gender", "male");
	set("long",
		"一頭軀幹魁梧如熊的巖魈﹐通體覆著青黑色的厚甲似的硬皮﹐與\n"
		"這六甲洞的岩壁渾然一色。牠是吸納了這六甲山千百年草木精氣\n"
		"的山精﹐已通了幾分靈性﹐一雙深陷的眼睛裡泛著幽幽的綠光﹐\n"
		"竟似帶著幾分思量。牠端坐在累累的獸骨之間﹐一身橫練的硬功\n"
		"刀槍難入﹐巨拳一握﹐筋骨格格作響﹐自有一股令百獸俯首、令\n"
		"勇者膽寒的兇威。山中相傳﹐這六甲山方圓百里的野獸﹐皆要奉\n"
		"牠為尊——非武藝精純、持械有備者﹐萬莫與牠為敵。\n");
	// 純 score：江湖歷練(升級)、拳腳精熟、武術造詣、武學之道、實戰經驗。無錢幣。
	set("bounty", ([
		"survive"         : 1100,
		"unarmed mastery" : 230,
		"martial art"     : 160,
		"martial mastery" : 96,
		"combat"          : 88,
	]));
	setup();
}

// 奉陪到底、凶悍反擊（牠並不主動撲路人﹐由玩家 kill 起釁）。
int accept_fight(object ob)
{
	do_chat((: command, "say 巖魈幽綠的眼裡凶光暴漲﹐霍然立起﹐巨拳挾著千鈞之力﹐迎面砸落﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
