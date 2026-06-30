// mistghost.c -- 霧魅，幻霧森林迷霧澗谷裡浮動的枯槁鬼影，獵場中段偏上獵物。
//
// 結構沿用 /d/langwo/npc/graywolf.c：可 kill、會還手、不主動攻擊路人(無
// attitude)，殺後只給 score(無錢)。戰力定在 level 24 一線——承霧狼(lvl20)往上、
// 為林心迷霧鬼魅(lvl28-30)之前的過渡。設定上是迷失林中、被霧氣纏住魂魄的孤魂
// 所化﹐然機制上仍走尋常 humanoid 戰鬥（不臆造特殊鬼怪機制——僅作氛圍描述）。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("霧魅", ({ "mist ghost", "mistghost", "ghost", "wumei" }) );
	// 根骨 30 → 形體上限約 150 點，半實半虛、纏鬥磨人，飄忽難纏。
	set_attr("con", 30);
	set_attr("str", 26);
	set_attr("dex", 30);
	set_race("human");
	set_class("commoner");
	set_level(24);

	// 身形飄忽、抓拿陰柔：閃躲最利，徒手拆招俱佳，內力漸厚。
	set_skill("unarmed", 38);
	set_skill("dodge", 34);
	set_skill("parry", 26);
	set_skill("force", 26);

	advance_stat("kee", 30);

	set("age", 30);
	set("gender", "male");
	set("long",
		"一道形容枯槁、半透不透的鬼影﹐約略還是個佝僂的人形﹐輕飄\n"
		"飄地不沾地面﹐在澗谷的水霧裡忽聚忽散。它周身泛著與磷火一\n"
		"般的青幽幽冷光﹐眼眶裡空洞洞地透出兩點寒星﹐死死綴住每一\n"
		"個闖進這澗谷的活人。村人說﹐這便是當年迷失在幻霧森林、再\n"
		"沒能走出去的旅人﹐魂魄被林中的霧氣纏住﹐困在了這水霧氤氳\n"
		"的澗谷裡——你若驚動了它﹐它便要與你纏鬥到底。\n");
	set("bounty", ([
		"survive"         : 300,
		"unarmed mastery" : 64,
		"martial art"     : 42,
		"martial mastery" : 22,
		"combat"          : 28,
	]));
	setup();
}

// 奉陪到底、陰冷反撲（它並不主動撲路人﹐由玩家 kill 起釁）。
int accept_fight(object ob)
{
	do_chat((: command, "say 霧魅空洞的眼眶裡寒光一閃﹐發出一聲嗚嗚的、不似人聲的悲嘯﹐飄飄忽忽地撲將過來﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
