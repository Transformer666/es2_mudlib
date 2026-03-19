// evil_hydra.c

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("鮫蛟", ({"evil_hydra", "hydra"}));

    set_attr("str", 25);
    set_attr("con", 24);
    set_attr("dex", 22);
    set_attr("spi", 20);
    set_race("human");
    set_class("fighter");
    set_level(60);
    advance_stat("gin", 500);
    advance_stat("kee", 500);

    set_skill("unarmed", 95);
    set_skill("dodge", 75);

    set("age", 1000);
    set("long",
        "一條蛇身龍首的水中巨獸，生有多頭，鱗片如濕潤的碧玉般閃\n"
        "爍著光澤，水氣環繞其身，令人不寒而慄。\n");

    setup();

    add_temp("apply/attack", 75);
    add_temp("apply/defense", 70);
    add_temp("apply/damage", 40);
    add_temp("apply/armor", 55);

    carry_money("silver", 50);
}
