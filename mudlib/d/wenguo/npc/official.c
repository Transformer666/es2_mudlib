// NPC: /d/wenguo/npc/official.c

#include <npc.h>

inherit F_SCHOLAR;

void create()
{
	set_name("文國縣令", ({"official", "magistrate"}));
	set_race("human");
	set_class("scholar");
	set_level(20);

	set("age", 50);
	set("gender", "male");
	set("long",
		"文國縣令身穿七品官服﹐頭戴烏紗帽﹐面容嚴肅而不失儒雅。\n"
		"他兩鬢微霜﹐目光如炬﹐舉手投足間透著一股正氣凜然的氣度。據\n"
		"說他是兩榜進士出身﹐為官清廉﹐深受百姓愛戴。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"文國縣令翻閱著案上的公文﹐不時提筆批註。\n",
		"文國縣令說道﹕為官一任﹐當造福一方百姓。\n",
		"文國縣令沉吟道﹕近來邊遠山區似有匪患﹐得派人巡查才是。\n",
	}));
	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
	carry_money("coin", 300);
}

int accept_fight(object ob)
{
	do_chat("文國縣令拍案而起﹕大膽﹗竟敢在衙門重地動武﹗來人﹗\n");
	return 0;
}
