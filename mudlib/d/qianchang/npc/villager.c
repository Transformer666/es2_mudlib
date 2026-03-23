// NPC: /d/qianchang/npc/villager.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("鎮民", ({"villager", "townfolk"}));
	set_race("human");
	set_class("commoner");
	set_level(5);

	set("age", 35);
	set("gender", "male");
	set("long", "一個普通的前場鎮居民，穿著粗布衣衫，皮膚黝黑，看得出是常年勞作的人。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"鎮民說道：前場鎮雖然不大，但南來北往的客商不少呢。\n",
		"鎮民嘆了口氣：今年的收成還算過得去。\n",
		"鎮民四處張望了一下，壓低聲音道：聽說最近路上有山賊出沒，出門要小心。\n",
	}));

	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
}
