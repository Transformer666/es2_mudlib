#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("狼翼弟子", ({"disciple", "langyi_disciple"}));
    set_attr("str", 14);
    set_attr("con", 13);
    set_attr("dex", 16);
    set_race("human");
    set_class("thief");
    set_level(12);

    set_skill("throwing", 30);
    set_skill("dodge", 28);
    set_skill("dagger", 25);

    set("age", 25);
    set("gender", "male");
    set("long",
        "一名狼翼堂的弟子﹐身穿夜行服﹐腰間別著幾把飛刀﹐目光冷冽。\n");
    setup();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_object( STOCK_WEAPON("dagger") )->wield();
    carry_money("coin", 35);
}
