// topaz_belt.c

#include <armor.h>

inherit F_WAIST_EQ;

void create()
{
    set_name("黃玉佩", ({"topaz belt", "topaz_belt"}));
    set_weight(800);
    setup_waist_eq();

    if( !clonep() ) {
        set("unit", "塊");
        set("value", 150000);
        set("long",
            "一塊雕琢精美的黃玉腰佩，玉質溫潤，散發著淡淡的暖光，佩戴時令人心神安寧。\n");
        set("wear_as", "waist_eq");
        set("apply_armor/waist_eq", ([
            "armor": 10,
        ]));
    }
    setup();
}
