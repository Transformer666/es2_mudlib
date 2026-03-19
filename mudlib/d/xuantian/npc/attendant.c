#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("侍從", ({"attendant", "shicong"}));
    set_attr("str", 10);
    set_attr("con", 10);
    set_attr("dex", 12);
    set_attr("int", 14);
    set_race("human");
    set_class("scholar");
    set_level(10);

    set_skill("sword", 20);

    set("age", 20);
    set("attitude", "peaceful");
    set("long",
        "一名玄天教的侍從﹐身穿青色長衫﹐正在安靜地抄寫經文。\n");
    setup();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_money("coin", 20);
}
