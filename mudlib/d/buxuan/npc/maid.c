#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("侍女", ({"maid", "shinyu"}));
    set_attr("str", 8);
    set_attr("con", 8);
    set_attr("dex", 12);
    set_race("human");
    set_class("commoner");
    set_level(5);

    set("age", 20);
    set("attitude", "peaceful");
    set("long",
        "一名年輕的侍女﹐身穿淡粉色的衣裙﹐正在打掃客房。\n");
    setup();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_money("coin", 10);
}
