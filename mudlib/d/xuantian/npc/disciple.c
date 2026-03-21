#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("玄天弟子", ({"disciple", "xuantian_disciple"}));
    set_attr("str", 12);
    set_attr("con", 12);
    set_attr("dex", 12);
    set_attr("int", 14);
    set_attr("wis", 14);
    set_race("human");
    set_class("taoist");
    set_level(10);

    set_skill("sword", 20);
    set_skill("dodge", 15);

    set("age", 21);
    set("gender", "male");
    set("attitude", "peaceful");
    set("long",
        "一名玄天教的弟子﹐身穿青色道袍﹐腰佩長劍﹐正在靜心修煉。\n");
    setup();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_object( STOCK_WEAPON("longsword") )->wield();
    carry_money("coin", 25);
}
