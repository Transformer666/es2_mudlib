// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("住持", ({"abbot", "monk", "zhuchi"}));
	set_race("human");
	set_class("commoner");
	set_level(20);
	set("age", 60);
	set("gender", "male");
	set_attr("wis", 22);
	set_attr("spi", 20);
	set_skill("unarmed", 40);
	set_skill("dodge", 35);
	set("long",
		"一位身披金色袈裟的年邁僧人，面容慈祥安詳，雙目半閉，彷\n"
		"彿時刻處於禪定之中。他主持著這座皇家寺院的一切佛事，佛學\n"
		"造詣深厚，德高望重。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"住持雙手合十，低聲誦道：阿彌陀佛，萬法皆空，唯心是實。\n",
		"住持緩緩說道：施主若心中有惑，不妨在佛前靜坐片刻，自會明了。\n",
		"住持輕敲木魚，殿中迴盪著悠遠的梵音。\n",
	}));

	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
	carry_money("coin", 100);
	set_temp("apply/vision_of_ghost", 1);
}

int accept_fight(object ob)
{
	do_chat("住持平靜地說道：阿彌陀佛，佛門淨地，不宜動武。施主請放下嗔念。\n");
	return 0;
}
