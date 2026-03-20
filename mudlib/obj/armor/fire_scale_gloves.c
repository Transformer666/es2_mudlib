// fire_scale_gloves.c

#include <armor.h>

inherit F_HAND_EQ;

void create()
{
    set_name("火鱗手套", ({"fire scale gloves", "fire_scale_gloves", "gloves"}));
    set_weight(800);
    setup_hand_eq();

    if( !clonep() ) {
        set("unit", "副");
        set("value", 240000);
        set("long",
            "一副以火鱗片鑲嵌的手套，指尖處隱約散發著熱氣，戴上後握\n"
            "劍的手更加穩定有力。\n");
        set("wear_as", "hand_eq");
        set("apply_armor/hand_eq", ([
            "armor": 15,
        ]));
    }
    setup();
}
