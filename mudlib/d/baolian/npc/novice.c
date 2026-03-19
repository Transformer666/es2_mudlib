#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("小沙彌", ({"novice", "shami"}));
    set_attr("str", 8);
    set_attr("con", 10);
    set_attr("dex", 10);
    set_race("human");
    set_class("monk");
    set_level(5);

    set("age", 12);
    set("attitude", "peaceful");
    set("long",
        "一名年幼的小沙彌﹐光著腦袋﹐穿著一件略嫌寬大的灰色僧\n"
        "袍﹐正在認真地擦拭佛像。\n");
    setup();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_money("coin", 5);
}
