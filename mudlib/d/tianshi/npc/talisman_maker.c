#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("符籙師", ({"talisman_maker", "fulu_shi"}));
    set_attr("str", 14);
    set_attr("con", 14);
    set_attr("dex", 18);
    set_attr("int", 22);
    set_attr("wis", 20);
    set_attr("spi", 22);
    set_race("human");
    set_class("taoist");
    set_level(30);

    set_skill("sword", 55);
    set_skill("taiyi sword", 50);
    set_skill("dodge", 45);

    set("age", 40);
    set("attitude", "peaceful");
    set("long",
        "一名符籙師﹐身穿黃色道袍﹐面前擺著朱砂和黃紙﹐正在專\n"
        "心繪製符籙。\n");
    setup();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_money("coin", 100);
}
