#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("莊丁", ({"servant", "zhuangding"}));
    set_attr("str", 12);
    set_attr("con", 12);
    set_attr("dex", 10);
    set_race("human");
    set_class("commoner");
    set_level(8);

    set("age", 30);
    set("attitude", "peaceful");
    set("long",
        "一名冷梅莊的莊丁﹐正在打掃院落。\n");
    setup();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_money("coin", 15);
}
