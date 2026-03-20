// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("廟祝", ({"monk", "miaozhu"}));
	set_race("human");
	set_class("commoner");
	set_level(12);

	set("age", 55);
	set("gender", "male");
	set("long",
		"一位年邁的僧人，身披素淨的袈裟，正細心地照料著殿中的香\n"
		"火供品。他以慈祥的微笑迎接每一位來訪者，雙手合十以示問候。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"廟祝雙手合十：阿彌陀佛，施主有禮了。\n",
		"廟祝輕聲說道：心誠則靈，佛祖自會保佑善心之人。\n",
		"廟祝緩緩添上幾柱清香，口中默默誦念經文。\n",
	}));

	set_attr("wis", 16);
	set_attr("spi", 15);
	set_skill("unarmed", 20);

	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
	carry_money("coin", 30);
	set_temp("apply/vision_of_ghost", 1);
}

int accept_fight(object ob)
{
	do_chat("廟祝搖頭道：阿彌陀佛，佛門清淨之地，不可妄動干戈。\n");
	return 0;
}
