// vim: syntax=lpc

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("白魚", ({"baiyu"}));
    set_attr("str", 24);
    set_attr("dex", 24);
    set_attr("con", 24);
    set_attr("int", 28);
    set_attr("spi", 30);
    set_attr("wis", 26);
    set_race("malik");
    set_class("commoner");
    set_level(70);

    set_skill("whip", 100);
    set_skill("dodge", 80);
    set_skill("parry", 70);
    set_skill("force", 90);

    set("age", 200);
    set("gender", "male");
    set("long", "「天神地鬼」白魚是「大漠八魔」的老大，屬於巫首族，"
        "約二百多歲。他精通奇門異術，手持一條怒天鞭，"
        "令人聞風喪膽。\n");
    setup();
    carry_object(STOCK_WEAPON("whip"))->wield();
    carry_object(STOCK_ARMOR("cloth"))->wear();
}
