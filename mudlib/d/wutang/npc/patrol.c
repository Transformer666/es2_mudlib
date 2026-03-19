// patrol.c

#include <npc.h>

inherit F_SOLDIER;

void create()
{
    set_name("巡邏兵", ({"patrol", "wutang_patrol"}));
    set_attr("str", 16);
    set_attr("con", 16);
    set_race("human");
    set_class("fighter");
    set_level(12);

    set_skill("sword", 50);
    set_skill("dodge", 40);

    set("age", 24);
    set("long", "一個身穿勁裝的巡邏兵﹐腰間佩著一把刀﹐正在街上巡邏。\n");
    setup();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_object( STOCK_WEAPON("longsword") )->wield();
    carry_money("coin", 80);
}
