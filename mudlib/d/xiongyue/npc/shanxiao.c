// shanxiao.c -- 山魈，熊月村後山月影深林深處盤踞的山中精怪，後山獵場巔峰之獸。
//
// 結構沿用 /d/heifeng/npc/greywolf.c(承 madwolf→rabbit)：可 kill、會還手、不主動
// 攻擊路人(無 attitude，由玩家 kill 起釁)，殺後只給 score(無錢)。戰力定在 level
// 36——任務交付獵場上限 25-40 之巔峰級，較黑熊(28)更刁鑽難纏：攀岩縱躍、身手矯
// 捷、略諳吐納內力，是後山獵場須備妥火候方克的對手。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("山魈", ({ "shanxiao", "mountain demon", "demon", "xiao" }) );
	set_attr("con", 36);
	set_attr("str", 34);
	set_attr("dex", 38);
	set_race("human");
	set_class("commoner");
	set_level(36);

	// 攀縱矯捷、爪牙刁鑽、略諳吐納：徒手、閃躲俱佳，拆招內力中上。
	set_skill("unarmed", 60);
	set_skill("dodge", 50);
	set_skill("parry", 44);
	set_skill("force", 40);

	// 厚其氣血、使之耐戰(參 greywolf advance_stat 之法)。
	advance_stat("kee", 60);
	advance_stat("gin", 30);

	set("age", 30);
	set("gender", "male");
	set("long",
		"一頭盤踞在巨岩陰處的山魈﹐形貌似猿而面目猙獰﹐生著一身赭\n"
		"紅的長毛﹐臂長過膝﹐一雙赤紅的眼睛在岩影裡幽幽地閃著兇光。\n"
		"牠是這月影深林裡的精怪﹐村人視之為山中之鬼﹐最善攀岩縱躍﹑\n"
		"來去如風。此刻牠倚石而踞﹐獠牙森森﹐喉間發出一串咯咯的怪\n"
		"笑﹐渾身的赭毛根根倒豎﹐後肢微屈﹐隨時要自那巨岩上猿縱而\n"
		"下﹐那股子刁鑽兇狡的氣息﹐教人不寒而慄。\n");
	// 純 score：江湖歷練(升級)、拳腳精熟、武術造詣、武學之道、實戰經驗。無錢幣。
	set("bounty", ([
		"survive"         : 620,
		"unarmed mastery" : 132,
		"martial art"     : 88,
		"martial mastery" : 44,
		"combat"          : 48,
	]));
	setup();
}

// 奉陪到底、刁鑽兇狡地反擊(牠並不主動撲路人﹐由玩家 kill 起釁)。
int accept_fight(object ob)
{
	do_chat((: command, "say 山魈喉間爆出一串淒厲的怪笑﹐赭毛倒豎﹐自巨岩上猿縱而下﹐獠牙利爪疾抓而來﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
