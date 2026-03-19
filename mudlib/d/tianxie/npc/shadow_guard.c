#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("暗衛", ({"shadow_guard", "guard"}));
    set_attr("str", 18);
    set_attr("con", 16);
    set_attr("dex", 22);
    set_race("human");
    set_class("warrior");
    set_level(35);

    set_skill("sword", 65);
    set_skill("dodge", 70);
    set_skill("parry", 55);

    set("age", 30);
    set("long",
        "一名身穿夜行衣的暗衛﹐身形矯健﹐行動悄無聲息。\n");
    setup();
    carry_object(__DIR__"obj/dark_blade")->wield();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_money("silver", 20);
}
