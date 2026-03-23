// NPC: /d/shuilan/npc/guard.c

#include <npc.h>

inherit F_SOLDIER;

void create()
{
    set_name("縣城守衛", ({"guard", "soldier"}));
    set_race("human");
    set_class("soldier");
    set_level(10);

    set("age", 25);
    set("gender", "male");
    set("long", "一個穿著官服的守衛﹐腰間佩著一把刀﹐看起來有些懶散。\n");
    setup();
    carry_object(STOCK_WEAPON("shortblade"))->wield();
    carry_object(STOCK_ARMOR("cloth"))->wear();
    carry_money("coin", 50);
}
