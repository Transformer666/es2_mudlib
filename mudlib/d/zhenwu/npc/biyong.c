// vim: syntax=lpc

#include <npc.h>

inherit F_SOLDIER;

void create()
{
	set_name("必勇", ({"biyong", "junshi"}));
	set_attr("str", 20);
	set_attr("dex", 22);
	set_attr("con", 20);
	set_attr("int", 26);
	set_attr("spi", 24);
	set_attr("wis", 28);
	set_race("woochan");
	set_class("commoner");
	set_level(50);

	set_skill("tactic", 120);
	set_skill("sword", 60);
	set_skill("dodge", 60);
	set_skill("parry", 50);

	set("age", 34);
	set("gender", "male");
	set("long",
		"必勇是振武軍營的軍師，官拜百戶。他雖然年僅三十四歲，卻精通\n"
		"戰術兵法，悟性極高，深受將士們的敬重。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"必勇凝視著案上的兵法圖，若有所思。\n",
		"必勇說道：兵者，詭道也。知己知彼，方能百戰不殆。\n",
	}));
	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
	carry_object(STOCK_WEAPON("longsword"))->wield();
	carry_money("coin", 200);
}
