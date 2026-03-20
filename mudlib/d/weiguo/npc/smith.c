// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("鐵匠", ({"smith", "blacksmith", "tiejiang"}));
	set_attr("str", 18);
	set_attr("con", 16);
	set_race("human");
	set_class("commoner");
	set_level(12);

	set_skill("unarmed", 25);

	set("age", 35);
	set("gender", "male");
	set("long",
		"一個肌肉虬結的鐵匠，臉上和手臂上沾滿了煤灰，正揮動著鐵錘\n"
		"猛力敲打著燒得通紅的金屬。他專門為駐軍打造和修補兵器，手藝精\n"
		"湛，遠近聞名。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"鐵匠擦了擦額頭的汗水，說道：好鋼要千錘百煉才成器啊。\n",
		"鐵匠端詳著剛打好的刀刃，滿意地點點頭：這批貨色不錯。\n",
		"鐵匠嘆道：軍營的訂單又催了，今晚怕是要趕工到半夜了。\n",
	}));
	set("no_fight", 1);

	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
	carry_money("coin", 60);
}
