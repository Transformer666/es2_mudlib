#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("龍圖學徒", ({"apprentice", "longttu_apprentice"}));
    set_attr("str", 10);
    set_attr("con", 10);
    set_attr("int", 14);
    set_attr("wis", 12);
    set_race("human");
    set_class("alchemist");
    set_level(10);

    set_skill("alchemy-medication", 20);

    set("age", 18);
    set("attitude", "peaceful");
    set("long",
        "一名龍圖丹派的學徒﹐年紀輕輕﹐正在專心研磨藥材。\n");
    setup();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_money("coin", 30);
}
