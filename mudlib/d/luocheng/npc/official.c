// official.c -- 雍府門前候見的謁客（純氣氛，烘托相府門庭與朝局暗潮）

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("謁客", ({ "petitioner", "yeke", "visitor" }) );
	set_attr("int", 16);
	set_race("human");
	set_class("scholar");
	set_level(8);

	set("age", 39);
	set("gender", "male");
	set("long",
		"一位捧著名帖、在相府門前候見的謁客﹐身著簇新的綢緞長\n"
		"衫﹐腰繫玉帶﹐衣冠楚楚。他在門前已等了大半個時辰﹐臉上\n"
		"卻不敢露出半分不耐﹐只賠著小心向府衛打聽相爺幾時得閒﹐\n"
		"那副熱中鑽營的模樣﹐瞞不過明眼人。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		"謁客捧著名帖﹐踮著腳往門裡張望﹐神色焦切。\n",
		"謁客向府衛賠著笑臉低聲道﹕勞煩通稟一聲﹐就說某某求見相爺﹐些許薄禮﹐還望笑納 ...\n",
		"謁客壓低聲音對你道﹕兄台也是來投謁相爺的﹖這雍府的門檻﹐可不是尋常人邁得進的喲。\n",
		"謁客感慨道﹕滿朝文武﹐誰不知相爺一句話便抵得旁人十年的苦熬。能在這門前遞上一張帖子﹐已是天大的體面了。\n",
	}));
	setup();
	carry_money("coin", 200);
}

int accept_fight(object ob)
{
	do_chat("謁客嚇得連名帖都掉了﹐連聲道﹕好漢饒命﹗這可是相府門前﹐你莫要連累了我﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
