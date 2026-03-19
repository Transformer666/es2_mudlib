// inferno_dog.c

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("鬼獫", ({"inferno_dog", "dog"}));

    set_attr("str", 28);
    set_attr("con", 25);
    set_attr("dex", 22);
    set_race("human");
    set_class("fighter");
    set_level(60);
    advance_stat("gin", 500);
    advance_stat("kee", 500);

    set_skill("unarmed", 100);
    set_skill("dodge", 80);

    set("age", 1000);
    set("long",
        "一頭被地獄之火環繞的巨犬，雙眸燃燒著猩紅的火焰，所過之處\n"
        "寸草不生，空氣中瀰漫著硫磺與灼熱的氣息。\n");

    setup();

    add_temp("apply/attack", 80);
    add_temp("apply/defense", 60);
    add_temp("apply/damage", 40);
    add_temp("apply/armor", 50);

    carry_money("silver", 50);
}
