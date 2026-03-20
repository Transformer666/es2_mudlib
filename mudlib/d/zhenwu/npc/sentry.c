// vim: syntax=lpc

#include <npc.h>

inherit F_SOLDIER;

void create()
{
	set_name("哨兵", ({"sentry", "guard", "shaobing"}));
	set_attr("str", 15);
	set_attr("con", 14);
	set_attr("dex", 14);
	set_race("human");
	set_class("commoner");
	set_level(16);

	set_skill("pike", 45);
	set_skill("dodge", 30);
	set_skill("parry", 35);

	set("age", 24);
	set("gender", "male");
	set("long",
		"一名年輕的哨兵筆直地站在瞭望塔上，手持長矛，警惕地注視著遠\n"
		"方。他的眼神銳利而專注，絲毫不敢懈怠，深知自己肩負著全營安危\n"
		"的重任。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"哨兵眯起眼睛望向遠處，喃喃道：那邊好像有動靜……不，是風吹草動罷了。\n",
		"哨兵握緊長矛，目光如炬地掃視著營外的每一條道路。\n",
		"哨兵揉了揉酸澀的眼睛，低聲嘆道：又是一夜沒合眼，可不能打瞌睡啊。\n",
	}));

	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
	carry_object(STOCK_WEAPON("pike"))->wield();
	carry_money("coin", 40);
}
