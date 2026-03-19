#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("哭笑門弟子", ({"disciple", "kuxiao_disciple"}));
    set_attr("str", 14);
    set_attr("con", 14);
    set_attr("dex", 16);
    set_race("human");
    set_class("warrior");
    set_level(20);

    set_skill("sword", 45);
    set_skill("dodge", 40);
    set_skill("parry", 35);

    set("age", 25);
    set("long",
        "一名哭笑門弟子﹐面帶一副半哭半笑的詭異表情。\n");
    setup();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_object( STOCK_WEAPON("longsword") )->wield();
    carry_money("coin", 40);
}
