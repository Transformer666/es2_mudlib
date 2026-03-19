// celestial_bull.c

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("饕餮", ({"celestial_bull", "bull"}));

    set_attr("str", 35);
    set_attr("con", 35);
    set_race("human");
    set_class("fighter");
    set_level(70);
    advance_stat("gin", 600);
    advance_stat("kee", 600);

    set_skill("unarmed", 120);
    set_skill("dodge", 50);

    set("age", 1500);
    set("long",
        "一頭體型大得難以置信的牛形巨獸，每踏出一步大地都為之震動，\n"
        "渾身散發著遠古洪荒的氣息，彷彿是從太初便已存在的凶物。\n");

    setup();

    add_temp("apply/attack", 120);
    add_temp("apply/defense", 50);
    add_temp("apply/damage", 80);
    add_temp("apply/armor", 100);

    carry_money("silver", 80);
}
