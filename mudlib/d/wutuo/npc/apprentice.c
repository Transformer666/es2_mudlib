#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("藥童", ({"apprentice", "yaotong"}));
    set_attr("str", 8);
    set_attr("con", 10);
    set_attr("int", 12);
    set_attr("wis", 10);
    set_race("human");
    set_class("alchemist");
    set_level(8);

    set("age", 14);
    set("attitude", "peaceful");
    set("long",
        "一名年幼的藥童﹐正在專心地研磨草藥。\n");
    setup();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_money("coin", 10);
}
