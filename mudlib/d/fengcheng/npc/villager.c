// NPC: /d/fengcheng/npc/villager.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("城中百姓", ({"villager", "citizen"}));
    set_race("human");
    set_class("commoner");
    set_level(2);

    set("age", 35);
    set("long", "一個穿著厚實皮襖的風城百姓﹐步履匆匆地趕路。\n");
    set("chat_chance", 1);
    set("chat_msg", ({
        "城中百姓搓了搓手﹐說道﹕今天風可真大啊。\n",
        "城中百姓裹緊了皮襖﹐低頭快步走過。\n",
    }));
    setup();
    carry_money("coin", 20);
}
