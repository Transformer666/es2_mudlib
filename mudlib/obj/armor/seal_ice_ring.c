// seal_ice_ring.c

#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("封印冰環", ({"seal ice ring", "seal_ice_ring"}));
    set_weight(80);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 220000);
        set("long",
            "一枚泛著冰藍色光芒的戒指，戒面凝結著永不消融的寒冰，據說能封印敵人的行動。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "armor": 6,
        ]));
    }
    setup();
}
