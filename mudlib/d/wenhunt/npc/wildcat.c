// wildcat.c -- 山狸，文國西山密林裡攀樹竄枝的花斑山貓，機警迅捷。
//
// 結構沿用 /d/heifeng/npc/greywolf.c：可 kill、會還手、不主動攻擊路人(無 attitude)，
// 殺後只給 score(無錢)。戰力定在 level 16 一線——文國山林獵場的入門對手，身手靈巧。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("山狸", ({ "wild cat", "wildcat", "cat", "shanli" }) );
	set_attr("con", 22);
	set_attr("str", 22);
	set_attr("dex", 30);
	set_race("human");
	set_class("commoner");
	set_level(16);

	// 攀樹竄枝極靈、撕咬尖利、閃躲迅捷﹐內力低平。
	set_skill("unarmed", 26);
	set_skill("dodge", 32);
	set_skill("parry", 18);
	set_skill("force", 12);

	set("age", 2);
	set("gender", "female");
	set("long",
		"一隻西山密林裡的山狸﹐生得一身斑駁的花毛﹐尖耳豎立﹐一雙碧\n"
		"綠的眼睛在林蔭裡幽幽放光。牠攀樹竄枝快如閃電﹐慣在密林間捕\n"
		"食鳥雀松鼠﹐爪牙尖利﹐極是機警。見了生人﹐牠或竄上高枝俯視﹐\n"
		"或弓背炸毛、發出一串嘶嘶的低吼﹐被逼急了便回身撕咬反撲。\n");
	// 純 score：江湖歷練(升級)、拳腳精熟、武術造詣、武學之道、實戰經驗。無錢幣。
	set("bounty", ([
		"survive"         : 160,
		"unarmed mastery" : 44,
		"martial art"     : 30,
		"martial mastery" : 16,
		"combat"          : 20,
	]));
	setup();
}

// 不主動撲路人﹐由玩家 kill 起釁；機警反撲。
int accept_fight(object ob)
{
	do_chat((: command, "say 山狸弓背炸毛﹐發出一串嘶嘶低吼﹐爪牙並施﹐縱身撲咬而上﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
