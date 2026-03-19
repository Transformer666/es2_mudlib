#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("暗衛", ({"dark_guard", "guard"}));
    set_attr("str", 14);
    set_attr("con", 14);
    set_attr("dex", 18);
    set_race("human");
    set_class("thief");
    set_level(20);

    set_skill("dagger", 45);
    set_skill("dodge", 50);
    set_skill("parry", 35);

    set("age", 28);
    set("long",
        "一名隱教暗衛﹐面無表情﹐身穿黑衣﹐靜靜地站崗守衛。\n");
    setup();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_money("coin", 60);
}
