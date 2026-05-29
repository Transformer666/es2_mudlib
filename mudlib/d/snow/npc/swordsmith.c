// swordsmith.c -- 劍甲門傳人 陳學亮（雪亭鎮打鐵鋪）
//
// 劍甲門以強化兵刃聞名。陳學亮在此設攤，替過往江湖客把手中兵器
// 開鋒淬煉、提升傷害（見 cmds/std/enchant.c）。
//
// 標記 set("enchant_master", 1)：enchant 指令以此判定房裡有無可強化兵器
// 的師傅。本 NPC 不賣東西（非 F_VENDOR），只提供強化服務。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("陳學亮", ({ "chen xueliang", "chen", "swordsmith" }) );
	set_race("human");
	set_class("fighter");
	set_level(20);
	set_stat_maximum("kee", 200);
	set_attr("str", 24);
	set_attr("cor", 20);
	set_attr("cps", 22);
	set_attr("dex", 21);
	set_attr("con", 20);

	set_skill("unarmed", 40);
	set_skill("parry", 40);
	set_skill("dodge", 30);
	set_skill("sword", 50);
	set_skill("blade", 40);
	set_skill("force", 30);

	set("age", 52);
	set("gender", "male");
	set("long",
		"這位精神矍鑠的老者便是劍甲門傳人陳學亮。他雙目炯炯有神﹐\n"
		"一雙手掌厚實有力﹐滿佈經年累月與爐火鐵砧打交道留下的繭與疤。\n"
		"劍甲門以強化兵刃聞名江湖﹐你可以用 enchant（或 強化）手持\n"
		"兵器請他開鋒淬煉﹐也可以用 ask 陳學亮 about 強化 打聽詳情。\n");

	// 供 enchant 指令辨識：此 NPC 為可強化兵刃的師傅。
	set("enchant_master", 1);

	set("chat_chance", 5);
	set("chat_msg", ({
		"陳學亮拿起一把兵器﹐就著爐火細細端詳刃口。\n",
		"陳學亮一邊掄錘敲打﹐一邊說道﹕好鋼還得千錘百煉。\n",
		"陳學亮說道﹕手裡有趁手兵刃的﹐不妨讓老朽替你開開鋒。\n",
		"陳學亮捋了捋鬍子﹐說道﹕劍甲門強化兵刃﹐只升不毀﹐儘管放心。\n",
		"陳學亮說道﹕兵刃強化各有其限﹐到了頂便再強不得了。\n",
	}));

	setup();
	carry_object("/obj/area/obj/cloth")->wear();
}

// 不與人動手，免得擂台變屠宰場。
int accept_fight()
{
	do_chat("陳學亮擺了擺手﹐說道﹕老朽只管打鐵﹐不與人動手。\n");
	return 0;
}

int accept_kill()
{
	return 0;
}

// ask 陳學亮 about 強化 / enchant
void accept_inquiry(object who, string topic)
{
	switch( topic ) {
	case "強化":
	case "enchant":
	case "劍甲門":
		command("say 劍甲門強化兵刃的法子﹐是把兵器架上爐火重新淬煉開鋒﹐"
			"教它傷人更利。");
		command("say 你只消手持想強化的兵器﹐對我說一聲 enchant（或 強化）便成﹐"
			"老朽自會收取些許銀兩。");
		command("say 兵器強得越多﹐工料越費﹐收費也就越貴﹔且各種兵刃都有其極限﹐"
			"到了頂便再強不得。此法只升不毀﹐你儘管放心。");
		break;
	default:
		command("say 這個老朽就不甚清楚了。");
		break;
	}
}

// vim: set ts=4 sw=4 syntax=lpc
