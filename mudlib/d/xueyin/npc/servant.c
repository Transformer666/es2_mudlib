#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("莊丁", ({"servant", "zhuangding"}));
    set_attr("str", 14);
    set_attr("con", 14);
    set_attr("dex", 12);
    set_race("human");
    set_class("warrior");
    set_level(15);

    set_skill("sword", 30);
    set_skill("dodge", 25);

    set("age", 28);
    set("long",
        "一名雪吟莊的莊丁﹐身穿黑色勁裝﹐腰間佩刀﹐正在巡邏。\n");
    setup();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_money("coin", 30);
}
