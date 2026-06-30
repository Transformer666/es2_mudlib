// marshgoose.c -- 蘆雁，婁縣水澤蘆蕩裡成群浮游的野雁，護窩極凶、撲翅啄人。
//
// 結構沿用 /d/heifeng/npc/greywolf.c：可 kill、會還手、不主動攻擊路人(無 attitude)，
// 殺後只給 score(無錢)。戰力定在 level 14 一線——婁縣水澤獵場的入門對手。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("蘆雁", ({ "marsh goose", "marshgoose", "goose", "luyan" }) );
	set_attr("con", 20);
	set_attr("str", 18);
	set_attr("dex", 26);
	set_race("human");
	set_class("commoner");
	set_level(14);

	// 撲翅啄人、閃躲靈巧﹐內力低微。
	set_skill("unarmed", 22);
	set_skill("dodge", 26);
	set_skill("parry", 12);
	set_skill("force", 8);

	set("age", 2);
	set("gender", "female");
	set("long",
		"一隻水澤裡的野雁﹐生得灰褐的羽毛、橙黃的扁喙﹐脖頸又長又靈\n"
		"活﹐成日在蘆蕩的淺水裡浮游覓食。這蘆雁看著溫馴﹐護起窩來卻\n"
		"極凶﹐見了生人闖近窩巢﹐便伸長脖子嘎嘎厲叫﹐張開兩翼撲楞楞\n"
		"地撲將上來﹐拿那硬喙沒頭沒臉地啄﹐連翅膀掃人也生疼。\n");
	// 純 score：江湖歷練(升級)、拳腳精熟、武術造詣、武學之道、實戰經驗。無錢幣。
	set("bounty", ([
		"survive"         : 130,
		"unarmed mastery" : 36,
		"martial art"     : 24,
		"martial mastery" : 14,
		"combat"          : 16,
	]));
	setup();
}

// 不主動撲路人﹐由玩家 kill 起釁；護窩凶撲。
int accept_fight(object ob)
{
	do_chat((: command, "say 蘆雁伸長脖子嘎嘎厲叫﹐張開兩翼撲楞楞地撲上﹐拿硬喙沒頭沒臉地啄來﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
