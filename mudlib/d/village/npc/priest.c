// priest.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("廟祝", ({"priest", "temple_priest"}));
	set_attr("str", 10);
	set_attr("con", 12);
	set_attr("int", 16);
	set_attr("spi", 18);
	set_race("human");
	set_class("commoner");
	set_level(12);

	set("age", 55);
	set("gender", "male");
	set("long",
		"一個身穿灰色布袍的老人﹐面容慈祥﹐鬚髮花白。他手持一柄\n"
		"竹帚﹐將廟裡打掃得一塵不染。看得出來他對這座小廟十分虔誠﹐\n"
		"日復一日地在此焚香祈福﹐守護著村子的安寧。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"廟祝在香爐前點了一炷香﹐閉目祈禱了片刻。\n",
		"廟祝說道﹕土地公保佑﹐今年風調雨順﹐五穀豐登。\n",
		"廟祝拿起竹帚﹐仔細地掃著廟裡的灰塵。\n",
	}));
	setup();
	carry_money("coin", 20);
}

int accept_fight(object ob)
{
	do_chat("廟祝連忙說道﹕施主﹐廟中不可動武﹐神靈在上﹐萬萬不可造次啊﹗\n");
	return 0;
}
