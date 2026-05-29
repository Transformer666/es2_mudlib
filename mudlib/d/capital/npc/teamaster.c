// teamaster.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("茶博士", ({ "teamaster", "vendor" }) );
	set_race("human");
	set_class("commoner");
	set_level(4);

	set("age", 45);
	set("gender", "male");
	set("long",
		"後海茶館裡資深的茶博士﹐手腳俐落﹐提著一柄長嘴的紫銅大\n"
		"壺﹐高沖低斟皆是一手好功夫。他見客人進門便堆起笑臉招呼。\n"
		"你可以用 list 看他供些什麼茶點﹐用 buy 向他點。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"茶博士提著長嘴銅壺﹐手腕一抖﹐一道水線不偏不倚地注滿了茶碗﹐滴水不灑。\n",
		"茶博士笑著招呼道﹕客官裡邊請﹐嚐嚐咱們後海茶館的新茶﹖\n",
		"茶博士一面斟茶一面閒話道﹕咱這後海湖的水﹐烹起茶來最是清甜﹐別處可比不得。\n",
	}));
	// 後海茶館供應茶點﹐暫沿用既有的乾糧吃食物件。
	// TODO: 日後可新建龍井、香片等茶飲 obj﹐及點心糕餅。
	set("merchandise", ([
		"/obj/food/mooncake" : 40,
		"/obj/food/manto" : 50,
		"/obj/food/dumpling" : 50,
	]));

	setup();
	carry_money("coin", 200);
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
}

int accept_fight(object ob)
{
	do_chat("茶博士連忙護住銅壺﹐賠笑道﹕客官息怒﹐這可是文雅之地﹐有話好說呀﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
