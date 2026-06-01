// azurewolf.c -- 青狼，狼窩谷狼牙石澗一帶出沒的野狼，精悍狡黠，已是頗硬的對手。
//
// 結構沿用 /d/wuling/npc/direwolf.c（承 /d/hudao/wild/npc/madwolf.c → rabbit.c）：
// 可 kill、會還手、不主動攻擊路人(無 attitude)，殺後只給 score(無錢)。戰力定在
// level 26 一線——較餓狼(20)更猛，慣於側翼包抄，是狼窩谷獵場接近高段的對手。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("青狼", ({ "azure wolf", "azurewolf", "wolf", "qinglang" }) );
	// 根骨 40 → 形體上限約 200 點；另以 advance_stat 加厚氣血，撲擊狡黠、耐戰。
	set_attr("con", 40);
	set_attr("str", 34);
	set_attr("dex", 28);
	set_race("human");
	set_class("commoner");
	set_level(26);

	// 撲擊狡黠、爪牙俱利：徒手與閃躲俱高，拆招、內力亦不弱。
	set_skill("unarmed", 44);
	set_skill("dodge", 30);
	set_skill("parry", 30);
	set_skill("force", 30);

	// 厚其氣血，使之耐打、有來有往（量輕於蒼狼幽谷的鐵背蒼狼）。
	advance_stat("kee", 70);

	set("age", 5);
	set("gender", "female");
	set("long",
		"一頭毛色青灰的野狼﹐周身的線條精悍而充滿爆發之力﹐較尋常\n"
		"灰狼更為狡黠。牠的毛色與這石澗的青灰岩壁渾然一色﹐慣於借\n"
		"著嶙峋的亂石掩蔽身形﹐悄沒聲地自側翼包抄﹐伺機撲擊咽喉。\n"
		"尋常獵戶遇上牠﹐往往連狼影都沒看清﹐喉頭便已被牠的利齒咬\n"
		"住。此刻牠壓低了身子﹐尾尖微微抖動﹐正蓄勢欲撲。\n");
	// 純 score：江湖歷練(升級)、拳腳精熟、武術造詣、武學之道、實戰經驗。無錢幣。
	set("bounty", ([
		"survive"         : 380,
		"unarmed mastery" : 90,
		"martial art"     : 60,
		"martial mastery" : 36,
		"combat"          : 40,
	]));
	setup();
}

// 奉陪到底、凶悍反擊（牠並不主動撲路人﹐由玩家 kill 起釁）。
int accept_fight(object ob)
{
	do_chat((: command, "say 青狼壓低身子﹐尾尖一抖﹐倏地化作一道青灰殘影自側翼撲擊而至﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
