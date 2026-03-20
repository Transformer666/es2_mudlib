// NPC: /d/jingji/npc/guard.c

#include <npc.h>

inherit F_SOLDIER;

void create()
{
	set_name("衙役", ({"guard", "yamen_guard"}));
	set_attr("str", 18);
	set_attr("con", 18);
	set_attr("dex", 16);
	set_race("human");
	set_class("fighter");
	set_level(16);

	set_skill("sword", 65);
	set_skill("parry", 55);
	set_skill("dodge", 50);

	set("age", 30);
	set("gender", "male");
	set("long",
		"一名身著皂衣的京畿衙役，腰佩鋼刀，目光銳利地掃視著廣場上\n"
		"來往的行人。他體格健壯，步伐沉穩，一看便知受過嚴格的訓練。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"衙役喝道：閒雜人等不得在此逗留！\n",
		"衙役警惕地環顧四周。\n",
	}));
	set("vendetta_mark", "authority");

	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
	carry_object(STOCK_WEAPON("broadsword"))->wield();
	carry_money("coin", 120);
}

int accept_fight(object ob)
{
	do_chat("衙役冷冷地說道：在京畿重地鬧事，你是不想活了嗎？\n");
	return 0;
}
