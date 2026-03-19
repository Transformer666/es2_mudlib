// frost_frog.c

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("寒蟾", ({"frost_frog", "frog"}));

    set_attr("str", 22);
    set_attr("con", 30);
    set_attr("spi", 20);
    set_race("human");
    set_class("fighter");
    set_level(55);
    advance_stat("gin", 450);
    advance_stat("kee", 450);

    set_skill("unarmed", 85);
    set_skill("dodge", 60);

    set("age", 700);
    set("long",
        "一隻覆滿冰晶的巨蟾，周圍的空氣都凝結成霜，寒氣逼人，雙\n"
        "目如兩顆冰藍色的寶石，冷冷地注視著一切。\n");

    setup();

    add_temp("apply/attack", 65);
    add_temp("apply/defense", 90);
    add_temp("apply/damage", 35);
    add_temp("apply/armor", 80);

    carry_money("silver", 40);
}
