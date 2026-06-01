// ironwolf.c -- 鐵背蒼狼，狼窩谷蒼狼幽谷中替狼王看守谷口的巨狼，極難纏。
//
// 結構沿用 /d/wuling/npc/direwolf.c（承 /d/hudao/wild/npc/madwolf.c → rabbit.c）：
// 可 kill、會還手、不主動攻擊路人(無 attitude)，殺後只給 score(無錢)。戰力定在
// level 36 一線——狼窩谷獵場最深處之外的大物，僅次於狼王，是須有相當火候、持械
// 方好應付的勁敵。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("鐵背蒼狼", ({ "iron-back wolf", "ironwolf", "wolf", "tiebei canglang" }) );
	set("nickname", "守谷者");
	// 根骨 56 → 形體上限約 280 點；另以 advance_stat 大幅加厚氣血，皮堅肉厚、極耐戰。
	set_attr("con", 56);
	set_attr("str", 48);
	set_attr("dex", 32);
	set_race("human");
	set_class("commoner");
	set_level(36);

	// 鐵背厚毛、撲擊勢沉力猛：徒手已近高手之境，拆招、內力俱強。
	set_skill("unarmed", 90);
	set_skill("dodge", 48);
	set_skill("parry", 52);
	set_skill("force", 60);

	// 厚其氣血，使之耐打、有來有往（仍輕於狼王的 kee+210）。
	advance_stat("kee", 150);

	set("age", 9);
	set("gender", "male");
	set("long",
		"一頭格外巨碩的蒼灰巨狼﹐肩高及人胸﹐脊背覆著一層鐵青色的\n"
		"厚毛﹐根根倒豎如針﹐尋常的刀劍竟難傷其分毫。牠是替狼王看\n"
		"守谷口的猛物﹐獨踞谷心的青石之上﹐連成群的青狼見了也要繞\n"
		"道而行。牠四爪穩穩踏在嶙峋的怪石上﹐脖頸低伏﹐喉間滾出一\n"
		"聲悠長而陰沉的低嗥﹐那聲音在封閉的幽谷裡來回激盪﹐震得人\n"
		"脊背生寒。\n");
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
	do_chat((: command, "say 鐵背蒼狼一聲震谷的長嗥﹐脊背鐵毛根根賁張﹐巨軀拔地撲向膽敢犯境的來人﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
