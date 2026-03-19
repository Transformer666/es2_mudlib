#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("鍛造匠", ({"smith", "duanzao_jiang"}));
    set_attr("str", 20);
    set_attr("con", 18);
    set_attr("dex", 16);
    set_race("human");
    set_class("alchemist");
    set_level(15);

    set_skill("sword", 30);
    set_skill("dodge", 20);

    set("age", 35);
    set("attitude", "peaceful");
    set("long",
        "一名鍛造匠﹐赤著上身﹐渾身肌肉結實﹐正在爐前揮錘鍛造。\n");
    setup();
    carry_object(__DIR__"obj/forge_hammer")->wield();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_money("coin", 50);
}
