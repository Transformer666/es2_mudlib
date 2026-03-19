// river_guard.c

#include <npc.h>

inherit F_SOLDIER;

void create()
{
	set_name("渡口守衛", ({"guard", "river_guard"}));
	set_attr("str", 18);
	set_attr("con", 18);
	set_attr("dex", 16);
	set_race("human");
	set_class("fighter");
	set_level(20);

	set_skill("sword", 70);
	set_skill("dodge", 60);
	set_skill("parry", 50);

	set("age", 30);
	set("long",
		"一個身穿皮甲的渡口守衛﹐手持長槍﹐警惕地注視著來往的行\n"
		"人。他的表情嚴肅﹐看得出是個盡忠職守的人。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"渡口守衛喝道﹕來者何人﹖報上名來﹗\n",
		"渡口守衛說道﹕最近河匪猖獗﹐各位行路要小心。\n",
		"渡口守衛嚴肅地巡視著四周。\n",
	}));
	setup();
	carry_object( STOCK_ARMOR("cloth") )->wear();
	carry_object( STOCK_WEAPON("longsword") )->wield();
	carry_money("coin", 120);
}
