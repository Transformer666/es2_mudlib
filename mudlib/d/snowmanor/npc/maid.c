// maid.c -- 雪吟莊婢女，廂廊侍奉（氣氛 NPC，受襲反擊）

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("婢女", ({ "maid", "binv" }));
	set("nickname", "莊上婢女");
	set_attr("str", 16);
	set_attr("dex", 19);
	set_attr("con", 17);
	set_race("human");
	set_class("commoner");
	set_level(8);

	set_skill("dodge", 40);
	set_skill("unarmed", 25);

	set("gender", "female");
	set("age", 18);
	set("long",
		"一名雪吟莊的青衣婢女﹐生得眉目清秀﹐卻總是低眉斂目﹐神色\n"
		"間透著幾分小心翼翼。她捧著茶水器皿﹐沿著廂廊輕步而行﹐連腳\n"
		"步聲都壓得極輕﹐顯是在這規矩森嚴的莊子裡﹐早已習慣了謹言慎\n"
		"行。\n");
	// 結仇標記：婢女雖柔弱﹐亦屬雪吟莊一脈﹔殺之會在玩家身上累積
	// vendetta/snow﹐其後雪吟莊 NPC 一見此玩家便主動圍攻（機制見 chard.c
	// 累積、attack.c init() 觸發﹐與官兵 authority 同理）。
	set("vendetta_mark", "snow");
	set("chat_chance", 3);
	set("chat_msg", ({
		"婢女捧著茶盤﹐低眉斂目地自你身邊輕步走過。\n",
		"婢女怯生生地福了一福﹕客人有甚麼吩咐麼﹖\n",
		"婢女壓低聲音道﹕莊上規矩大﹐客人說話 ... 還是輕些好。\n",
	}));
	setup();
	carry_object("/obj/area/obj/cloth")->wear();
	carry_money("coin", 15);
}

// 婢女柔弱﹐被襲也只能驚惶反抗。雪吟莊結仇已透過 vendetta_mark 接上。
int accept_fight(object ob)
{
	do_chat((: command, "say 啊﹗來人哪﹗有人行兇啊﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
