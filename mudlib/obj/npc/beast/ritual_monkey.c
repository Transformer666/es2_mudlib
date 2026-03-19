// ritual_monkey.c

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("靈狙", ({"ritual_monkey", "monkey"}));

    set_attr("str", 20);
    set_attr("con", 18);
    set_attr("dex", 28);
    set_attr("spi", 25);
    set_race("human");
    set_class("fighter");
    set_level(55);
    advance_stat("gin", 450);
    advance_stat("kee", 450);

    set_skill("unarmed", 90);
    set_skill("dodge", 100);

    set("age", 800);
    set("long",
        "一隻銀毛古猿，渾身散發著靈性的光輝，雙目如星，動作敏捷\n"
        "如風，彷彿能洞察世間萬物的玄機。\n");

    setup();

    add_temp("apply/attack", 70);
    add_temp("apply/defense", 80);
    add_temp("apply/damage", 30);
    add_temp("apply/armor", 40);

    carry_money("silver", 40);
}
