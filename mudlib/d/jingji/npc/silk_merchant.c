// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("綢緞商人", ({"merchant", "silk_merchant", "trader"}));
	set_race("human");
	set_class("commoner");
	set_level(10);
	set("age", 45);
	set("gender", "male");
	set("long",
		"一位衣著華麗的綢緞商人，身穿上等蜀錦長袍，正在攤位前展\n"
		"示著五彩繽紛的絲綢和各種精緻的織品。他面帶殷勤的微笑，言\n"
		"辭間盡是花團錦簇的客套話。\n");
	set("merchandise", ([
		STOCK_ARMOR("cloth") : 30,
		STOCK_ARMOR("robe") : 15,
	]));
	set("chat_chance", 1);
	set("chat_msg", ({
		"綢緞商人笑容滿面地招呼道：客官請看，這可是上等的蘇杭絲綢，天下聞名啊！\n",
		"綢緞商人得意地說道：京畿乃天下貨物匯聚之地，別處可買不到這般好貨。\n",
		"綢緞商人撫摸著一匹綢緞道：這批雲錦是從江南剛運來的，摸摸這手感……\n",
	}));

	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
	carry_money("coin", 800);
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
}

int accept_fight(object ob)
{
	do_chat("綢緞商人連連擺手道：客官息怒，有話好說，何必動粗呢！\n");
	return 0;
}
