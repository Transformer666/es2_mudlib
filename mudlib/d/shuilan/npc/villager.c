// NPC: /d/shuilan/npc/villager.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("縣城居民", ({"villager", "citizen"}));
    set_race("human");
    set_class("commoner");
    set_level(2);

    set("age", 33);
    set("long", "一個普通的水嵐縣居民﹐穿著樸素﹐撐著一把油紙傘。\n");
    set("chat_chance", 1);
    set("chat_msg", ({
        "縣城居民說道﹕今天霧又大了﹐走路都看不太清。\n",
        "縣城居民撐著傘﹐慢慢走過。\n",
    }));
    setup();
    carry_money("coin", 20);
}
