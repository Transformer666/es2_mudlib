// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("小尼姑", ({"novice", "xiaoni"}));
    set_attr("str", 8);
    set_attr("con", 9);
    set_attr("dex", 11);
    set_race("human");
    set_class("monk");
    set_level(5);

    set("age", 14);
    set("gender", "female");
    set("attitude", "peaceful");
    set("long",
        "一名年輕的小尼姑﹐穿著一件略嫌寬大的灰色僧袍﹐正安靜地\n"
        "誦讀著經書。\n");
    setup();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_money("coin", 5);
}
