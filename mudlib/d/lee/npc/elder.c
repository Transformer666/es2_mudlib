// elder.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("李老伯", ({"elder", "li_elder"}));
	set_race("human");
	set_class("commoner");
	set_level(10);

	set("age", 70);
	set("long",
		"一個精神矍鑠的老人﹐鬚髮皆白﹐穿著一件整潔的青布長衫。\n"
		"他拄著一根龍頭拐杖﹐在村裡慢悠悠地踱步﹐遇到人便和藹地點\n"
		"頭微笑。他是李家村的族長﹐在村裡德高望重。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"李老伯捋著白鬍子﹐笑道﹕客人遠道而來﹐歡迎歡迎。\n",
		"李老伯嘆道﹕我李家在此居住已有百年了﹐見過的事多了去啦。\n",
		"李老伯說道﹕嚐嚐我們李家的豆腐﹐那可是祖傳的手藝。\n",
		"李老伯拄著拐杖﹐慢悠悠地走著﹐不時跟路過的村民寒暄。\n",
	}));
	setup();
	carry_money("coin", 40);
}
