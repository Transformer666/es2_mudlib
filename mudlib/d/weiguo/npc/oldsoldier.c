// oldsoldier.c -- 衛國鎮門洞下看門的老卒（純氣氛閒談）。
//                 早年屯軍留下的老人﹐守著這座再不關的關門﹐閒話些戍邊的舊事。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("看門老卒", ({ "oldsoldier", "gate guard", "kanmenlaozu" }) );
	set("nickname", "看門老卒");
	set_race("human");
	set_class("commoner");
	set_level(5);

	set("age", 62);
	set("gender", "male");
	set("long",
		"一個看門的老卒﹐搬了張矮凳坐在門洞下曬太陽﹐穿著件褪\n"
		"色的舊號褂﹐想是早年屯軍裡留下的老人。他身板還算硬朗﹐只\n"
		"是一條腿走起來微微跛著﹐想是當年戍邊落下的。他守著這座再\n"
		"不關的關門﹐成日價嗑著瓜子﹐與過往的鎮民有一搭沒一搭地招\n"
		"呼﹐倒也清閒自在。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		"看門老卒嗑著瓜子﹐瞇眼瞧著門洞裡進進出出的鎮民﹐偶爾和相熟的點頭招呼。\n",
		"看門老卒伸手摩挲著門邊那方刻著「衛國」的石匾﹐神色裡透著幾分追憶。\n",
		"看門老卒捶了捶那條微跛的腿﹐悠悠地道﹕這腿啊﹐是早年守關落下的﹐一變天就酸。\n",
	}));
	setup();
	carry_money("coin", 20);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想跟這老卒打聽甚麼﹖（試試 ask oldsoldier about 衛國，或 ask oldsoldier about 關門）\n");

	if( arg == "oldsoldier about 衛國"
	||  arg == "oldsoldier about 衛國鎮"
	||  arg == "oldsoldier about 關門"
	||  arg == "oldsoldier about 關"
	||  arg == "oldsoldier about 鎮"
	||  arg == "oldsoldier about weiguo" ) {
		do_chat(({
			(: command, "say 客官打外頭來罷﹖這座關門﹐早年可是戍邊的要隘﹐關門一閉﹐連隻雀兒也飛不進來。老朽當年就在這牆頭站崗放哨﹐風裡雨裡﹐一站就是半宿。" :),
			(: command, "say 如今邊事平了﹐屯軍也撤了﹐這關門再不曾合過﹐老朽這把老骨頭﹐也就守著它曬曬太陽、看看門。太平日子好啊﹐客官只管進鎮去﹐鎮裡安生著哩。" :),
		}));
		return 1;
	}

	return notify_fail("看門老卒嗑著瓜子憨憨一笑﹕客官問這個做甚﹖太平地界﹐進鎮去逛逛罷。\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎喲﹗客官這是做甚﹖老朽一個看門的退伍老卒﹐與你無冤無仇哪﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
