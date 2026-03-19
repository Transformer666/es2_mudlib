#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("棄徒", ({"renegade", "qitu"}));
    set_attr("str", 16);
    set_attr("con", 16);
    set_attr("dex", 18);
    set_race("human");
    set_class("warrior");
    set_level(25);

    set_skill("sword", 50);
    set_skill("dodge", 45);
    set_skill("parry", 40);

    set("age", 30);
    set("long",
        "一名被逐出師門又被莊主收留的棄徒﹐面容陰鬱﹐眼神中透\n"
        "著一股不甘。\n");
    setup();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_object( STOCK_WEAPON("longsword") )->wield();
    carry_money("silver", 10);
}
