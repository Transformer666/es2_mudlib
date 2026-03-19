#include <npc.h>

inherit F_SCHOLAR;

void create()
{
    set_name("門生", ({"disciple", "buxuan_disciple"}));
    set_attr("str", 12);
    set_attr("con", 12);
    set_attr("dex", 14);
    set_attr("int", 16);
    set_race("human");
    set_class("scholar");
    set_level(15);

    set_skill("sword", 30);
    set_skill("dodge", 25);

    set("age", 22);
    set("attitude", "peaceful");
    set("long",
        "一名步玄派的門生﹐身穿白色長衫﹐正在認真地練劍。\n");
    setup();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_object( STOCK_WEAPON("longsword") )->wield();
    carry_money("coin", 50);
}
