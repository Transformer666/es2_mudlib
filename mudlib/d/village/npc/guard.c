// guard.c

#include <npc.h>

inherit F_SOLDIER;

void create()
{
	set_name("村莊守衛", ({"guard", "village guard"}));
	set_attr("str", 18);
	set_attr("con", 16);
	set_attr("dex", 14);
	set_race("human");
	set_class("fighter");
	set_level(15);

	set_skill("sword", 55);
	set_skill("dodge", 45);
	set_skill("parry", 40);

	set("age", 28);
	set("gender", "male");
	set("long",
		"一個身材魁梧的青年漢子﹐穿著一件粗布短褂﹐腰間挎著一把\n"
		"樸實的長刀。他站在村口﹐警惕地注視著來往的行人﹐雖然裝備\n"
		"簡陋﹐但眼神中透著一股不容侵犯的堅毅。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"守衛掃視了四周一眼﹐一切安好。\n",
		"守衛說道﹕最近野外不太平﹐出村要小心。\n",
		"守衛伸了個懶腰﹐又打起精神來繼續站崗。\n",
	}));
	setup();
	carry_object( STOCK_WEAPON("longsword") )->wield();
	carry_object( STOCK_ARMOR("cloth") )->wear();
	carry_money("coin", 50);
}
