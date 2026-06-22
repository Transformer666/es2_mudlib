// tianao.c -- 天獒，天山雪線之上盤踞的高寒猛獸，冰稜道與雪窟一帶出沒。
//
// 結構沿用 /d/langwo/npc/azurewolf.c（承 /d/heifeng/npc/greywolf.c → rabbit.c）：
// 可 kill、會還手、不主動攻擊路人(無 attitude)，殺後只給 score(無錢)。戰力定在
// level 56 一線——較狼窩谷的鐵背蒼狼(36)更硬，與道士素雲書 lv60 傳送點門檻相稱，
// 是天山獵場供中階玩家練功的主力對手。多隻可重生(房間 objects 配重生)。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("天獒", ({ "tibetan mastiff", "mastiff", "tianao", "ao" }) );
	// 根骨 60 → 形體上限頗厚；另以 advance_stat 大幅加厚氣血，耐高寒、極耐戰。
	set_attr("con", 60);
	set_attr("str", 52);
	set_attr("dex", 38);
	set_race("human");
	set_class("commoner");
	set_level(56);

	// 撲擊剛猛、爪牙俱利、慣於高寒：徒手已近高手之境，閃躲、拆招、內力俱強。
	set_skill("unarmed", 120);
	set_skill("dodge", 60);
	set_skill("parry", 64);
	set_skill("force", 70);

	// 厚其氣血，使之耐打、有來有往（量輕於雪窟領頭的白睛巨獒）。
	advance_stat("kee", 200);

	set("age", 6);
	set("gender", "male");
	set("long",
		"一頭體形雄健的天山天獒﹐肩高及人腰﹐周身覆著一層厚密的灰\n"
		"褐長毛﹐毛梢綴著未化的碎雪﹐風過處根根倒豎。牠是天山雪線\n"
		"之上特有的猛獸﹐生性兇悍、慣於高寒﹐獠牙森森、目光如電﹐\n"
		"連成群的雪狼見了也要繞道而行。此刻牠四爪穩穩踏在覆雪的冰\n"
		"稜上﹐脖頸低伏、前肢微屈﹐喉間滾出一聲沉沉的悶吼﹐那聲音\n"
		"在背陰的山坳裡來回激盪﹐聽得人脊背發寒。\n");
	// 純 score：江湖歷練(升級)、拳腳精熟、武術造詣、武學之道、實戰經驗。無錢幣。
	set("bounty", ([
		"survive"         : 1600,
		"unarmed mastery" : 300,
		"martial art"     : 200,
		"martial mastery" : 120,
		"combat"          : 110,
	]));
	setup();
}

// 奉陪到底、凶悍反擊（牠並不主動撲路人﹐由玩家 kill 起釁）。
int accept_fight(object ob)
{
	do_chat((: command, "say 天獒脖頸一沉﹐豎起滿身灰褐長毛﹐發出一聲震坳的悶吼﹐弓身疾撲而上﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
