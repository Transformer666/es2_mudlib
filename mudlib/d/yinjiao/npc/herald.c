#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("黑龍使者", ({"herald", "heilong_shizhe"}));
    set_attr("str", 18);
    set_attr("con", 16);
    set_attr("dex", 22);
    set_race("human");
    set_class("thief");
    set_level(30);

    set_skill("dagger", 60);
    set_skill("dodge", 65);
    set_skill("parry", 50);

    set("age", 35);
    set("long",
        "一名黑龍使者﹐身穿黑色勁裝﹐面蒙黑巾﹐只露出一雙銳利\n"
        "的眼睛。\n");
    setup();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_money("silver", 20);
}
