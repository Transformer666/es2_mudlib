// NPC: /d/lee/npc/hall_keeper.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("祠堂管事", ({"hall_keeper", "keeper"}));
	set_race("human");
	set_class("commoner");
	set_level(8);

	set("age", 58);
	set("gender", "male");
	set("long",
		"一個頭髮半白的老人﹐穿著一件整潔的深藍長衫﹐腰間繫著一\n"
		"串鑰匙。他是李家祠堂的管事﹐負責打掃祠堂、看管祭器﹐每逢\n"
		"節令還要張羅祭祀的事宜。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"管事擦拭著供桌上的香爐﹐嘴裡唸叨﹕祖宗保佑。\n",
		"管事望著牆上的先人畫像﹐若有所思。\n",
		"管事在牌位前點上了一炷香。\n",
	}));

	setup();
	carry_money("coin", 15);
}
