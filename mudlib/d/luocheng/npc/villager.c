// NPC: /d/luocheng/npc/villager.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("城中居民", ({"villager", "citizen"}));
    set_race("human");
    set_class("commoner");
    set_level(2);

    set("age", 30);
    set("long", "一個普通的羅城居民﹐穿著得體﹐步履匆匆地趕路。\n");
    set("chat_chance", 1);
    set("chat_msg", ({
        "城中居民說道﹕羅城的生意可越來越好做了。\n",
        "城中居民東張西望﹐似乎在找什麼人。\n",
    }));
    setup();
    carry_money("coin", 25);
}
