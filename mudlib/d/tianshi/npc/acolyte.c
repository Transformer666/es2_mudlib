#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("道童", ({"acolyte", "daotong"}));
    set_attr("str", 10);
    set_attr("con", 10);
    set_attr("dex", 12);
    set_attr("spi", 14);
    set_race("human");
    set_class("taoist");
    set_level(12);

    set_skill("sword", 25);
    set_skill("dodge", 20);

    set("age", 16);
    set("attitude", "peaceful");
    set("long",
        "一名年輕的道童﹐身穿藍色道袍﹐手持一把小掃帚﹐正在清\n"
        "掃庭院。\n");
    setup();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_money("coin", 20);
}
