// runner.c -- 羅城廣場上奔走的相府僕從（純氣氛，烘托相府的赫赫家聲）

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("相府僕從", ({ "runner", "servant", "puren" }) );
	set_race("human");
	set_class("commoner");
	set_level(3);

	set("age", 28);
	set("gender", "male");
	set("long",
		"一個相府裡使喚的僕從﹐穿著體面的青布短褂﹐胸前繡著一\n"
		"個小小的「雍」字﹐手裡捧著拜帖與采辦的單子﹐在廣場上來\n"
		"去匆匆。他仗著主家的勢﹐連走路都帶著三分趾高氣揚﹐尋常\n"
		"小民他是不大瞧得上眼的。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		(: random_move :),
		"相府僕從捧著一疊拜帖﹐昂著頭穿過廣場﹐神氣得很。\n",
		"相府僕從斜著眼打量你一眼﹐哼了一聲﹐並不搭話。\n",
		"相府僕從向相熟的小販道﹕府裡今兒個又要待客﹐這采辦的單子長著哩﹐快着些備齊了送去。\n",
		"相府僕從壓低聲音得意道﹕咱們相爺如今聖眷正隆﹐這滿朝的文武﹐有幾個不看著相府的臉色行事﹖\n",
	}));
	setup();
	carry_money("coin", 40);
}

int accept_fight(object ob)
{
	do_chat("相府僕從跳開一步﹐尖聲嚷道﹕反了你了﹗也不打聽打聽這是誰家門前﹗府衛﹗還不拿下﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
