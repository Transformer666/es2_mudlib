// NPC: /d/green_n/npc/wild_horse.c

#include <npc.h>

inherit F_FIGHTER;

void create()
{
	set_name("草原野馬", ({"wild horse", "horse"}));
	set_race("animal");
	set_class("commoner");
	set_level(12);

	set("age", 6);
	set("long",
		"一匹毛色棕紅的草原野馬，四肢修長有力，鬃毛在風中飄揚。\n"
		"牠的眼神機警而靈動，隨時準備撒開四蹄奔馳而去。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"野馬甩了甩長長的鬃毛，低頭啃食青草。\n",
		"野馬揚起前蹄，發出一聲響亮的嘶鳴。\n",
	}));

	setup();
}

int accept_fight(object ob)
{
	do_chat("野馬受驚似的向後退了幾步，打著響鼻。\n");
	return 0;
}
