#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("蒹葭弟子", ({"disciple", "jianjia_disciple"}));
    set_attr("str", 14);
    set_attr("con", 13);
    set_attr("dex", 15);
    set_race("human");
    set_class("fighter");
    set_level(12);

    set_skill("sword", 30);
    set_skill("dodge", 25);
    set_skill("parry", 20);

    set("age", 22);
    set("gender", "male");
    set("long",
        "一名蒹葭門的弟子﹐身穿短打勁裝﹐腰掛長劍﹐正在專心試劍。\n");
    setup();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_object( STOCK_WEAPON("longsword") )->wield();
    carry_money("coin", 30);
}
