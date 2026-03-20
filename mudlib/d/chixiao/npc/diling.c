// NPC: /d/chixiao/npc/diling.c - 地靈 Boss NPC

#include <npc.h>

inherit F_FIGHTER;

void create()
{
	set_name("地靈", ({"diling", "di_ling"}));
	set_attr("str", 30);
	set_attr("dex", 24);
	set_attr("con", 30);
	set_attr("int", 22);
	set_attr("wis", 20);
	set_attr("spi", 28);
	set_attr("cps", 26);
	set_race("spirit");
	set_class("warrior");
	set_level(70);

	set_skill("axe", 120);
	set_skill("unarmed", 100);
	set_skill("dodge", 90);
	set_skill("parry", 110);
	set_skill("force", 110);
	set_skill("dragon force", 120);
	map_skill("force", "dragon force");

	advance_stat("gin", 300);
	advance_stat("kee", 350);
	advance_stat("sen", 150);

	set("age", 0);
	set("gender", "male");
	set("attitude", "aggressive");
	set("long",
		"大地震動﹐一道褐黃色的光柱從地底衝出﹐凝聚成一個高大威\n"
		"猛的人形﹐這就是地靈。他的身軀如同岩石一般堅硬﹐表面佈滿\n"
		"了龜裂的紋路﹐隱隱透出暗紅色的光芒。地靈的雙目如同深淵﹐\n"
		"令人望而生畏。他每踏出一步﹐腳下的大地便微微顫抖。\n");

	set("chat_chance_combat", 8);
	set("chat_msg_combat", ({
		"地靈一拳擊向地面﹐大地猛烈震動﹗\n",
		"地靈沉聲道﹕螻蟻之輩﹐安敢擾我沉睡﹗\n",
		"地靈周身土石飛揚﹐一股沉重的力量向四周壓迫而來。\n",
	}));

	setup();
	carry_object(STOCK_WEAPON("axe"))->wield();
	set_temp("apply/vision_of_ghost", 1);
}

void die(object killer)
{
	if( killer && userp(killer) ) {
		tell_object(killer,
			"地靈的身軀轟然碎裂﹐化為漫天飛舞的土石。\n"
			"一柄散發著大地之力的雙手斧和一顆脈動著生命力的靈心\n"
			"從碎石中緩緩浮現。\n");
	}
	::die(killer);
}
