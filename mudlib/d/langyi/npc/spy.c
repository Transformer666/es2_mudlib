#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("瑯夷暗探", ({"spy", "langyi_spy"}));
    set_attr("str", 12);
    set_attr("con", 12);
    set_attr("dex", 18);
    set_race("human");
    set_class("thief");
    set_level(20);

    set_skill("dagger", 45);
    set_skill("dodge", 50);
    set_skill("parry", 35);

    set("age", 28);
    set("long",
        "一名身穿灰衣的瑯夷暗探﹐面容普通﹐放在人群中毫不起眼。\n");
    setup();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_money("coin", 80);
}
