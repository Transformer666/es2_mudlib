// NPC: /d/qianchang/npc/temple_keeper.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("廟祝", ({"temple keeper", "keeper"}));
	set_race("human");
	set_class("commoner");
	set_level(6);

	set("age", 60);
	set("gender", "male");
	set("long",
		"一個清瘦的老人，鬚髮皆白，穿著一件素色的粗布長袍。他手\n"
		"持一把竹掃帚，慢悠悠地打掃著廟前的落葉，神態安詳平和。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"廟祝雙手合十道：施主誠心祈禱，土地公自會保佑。\n",
		"廟祝往香爐裡添了一炷香，青煙嫋嫋升起。\n",
		"廟祝輕聲說道：前場鎮雖小，但有土地公庇佑，一直平平安安的。\n",
	}));

	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
}
