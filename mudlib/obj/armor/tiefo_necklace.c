// tiefo_necklace.c

#include <armor.h>

inherit F_NECK_EQ;

void create()
{
    set_name("鐵佛珠", ({"tiefo necklace", "tiefo_necklace", "necklace"}));
    set_weight(500);
    setup_neck_eq();

    if( !clonep() ) {
        set("unit", "串");
        set("value", 150000);
        set("long",
            "一串以玄鐵打造的佛珠，每顆珠子都沉甸甸的，散發著莊嚴肅\n"
            "穆的氣息，既是念珠亦是暗器。\n");
        set("wear_as", "neck_eq");
        set("apply_armor/neck_eq", ([
            "armor": 10,
        ]));
    }
    setup();
}
