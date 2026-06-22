// chief.c -- 莽林盜匪頭目，據盜窟聚義的悍匪首腦，莽林獵場的巔峰對手。
//
// 結構沿用 /d/heifeng/npc/greywolf.c 之 score 範式 + /d/wutang/npc/escort.c
// 之持械人形（fighter + blade + carry STOCK_WEAPON("broadsword")->wield()）。
// 戰力定在 level 34 一線——較嘍囉(27)厚實兇悍，已諳吐納、身手老辣，是焱硝村
// /莽林這片填充獵場的最強之敵。殺後 bounty 較厚（仍無錢，純 score-only 獵場）。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("盜匪頭目", ({ "chief", "bandit chief", "toumu" }) );
	set("nickname", "盜匪頭目");
	set_attr("str", 38);
	set_attr("con", 38);
	set_attr("dex", 30);
	set_race("human");
	set_class("fighter");
	set_level(34);

	// 久經拼殺、刀法老辣、拆招閃躲俱精﹐內力亦較嘍囉深厚。
	set_skill("blade", 64);
	set_skill("parry", 50);
	set_skill("dodge", 44);
	set_skill("unarmed", 42);
	set_skill("force", 38);

	// 厚其氣血﹐使之耐打、有來有往（參 greywolf advance_stat 之法﹐量稍重）。
	advance_stat("kee", 50);

	set("age", 42);
	set("gender", "male");
	set("long",
		"這是聚嘯莽林的盜匪頭目﹐生得身形魁梧、虎背熊腰﹐滿臉橫肉\n"
		"間一道猙獰的刀疤自額角直劃到腮邊﹐更添三分煞氣。他穿一身\n"
		"半舊的皮甲﹐腰挎一柄厚背闊刀﹐叉著腰踞坐在窟中那塊大青石\n"
		"上﹐睥睨四下﹐手底下一夥嘍囉惟他馬首是瞻。多少孤身行旅誤\n"
		"闖進這莽林盜窟﹐便都折在了他這柄闊刀之下——他是這片莽林裡\n"
		"說一不二的草頭王。\n");
	// 純 score（頭目級較厚）：江湖歷練(升級)、刀法精熟、武術造詣、武學之道、實戰經驗。無錢幣。
	set("bounty", ([
		"survive"         : 620,
		"blade mastery"   : 130,
		"martial art"     : 90,
		"martial mastery" : 44,
		"combat"          : 42,
	]));
	setup();
	carry_object( STOCK_WEAPON("broadsword") )->wield();
}

// 奉陪到底、凶悍反擊（不主動撲路人﹐由玩家 kill 起釁）。
int accept_fight(object ob)
{
	do_chat((: command, "say 盜匪頭目仰天一陣獰笑﹕好大的膽子﹐竟敢闖老子的山頭﹗弟兄們﹐宰了他﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
