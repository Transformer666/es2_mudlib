// villager.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("村民", ({"villager", "sanyen_villager"}));
	set_race("human");
	set_class("commoner");
	set_level(5);

	set("age", 40);
	set("gender", "male");
	set("long", "一個面帶愁容的村民﹐看起來飽經風霜。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"村民嘆了口氣﹐說道﹕山上那些強盜三天兩頭下來搶東西﹐苦啊。\n",
		"村民壓低聲音說道﹕聽說廟裡的和尚功夫很厲害﹐可惜他不管閒事。\n",
		"村民搖搖頭﹐匆匆走開了。\n",
	}));
	setup();
	carry_money("coin", 10);
}
