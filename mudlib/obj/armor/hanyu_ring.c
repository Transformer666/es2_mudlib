// hanyu_ring.c

#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("漢玉戒指", ({"hanyu ring", "hanyu_ring", "ring"}));
    set_weight(30);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 100000);
        set("long",
            "一枚以上等漢玉雕琢而成的戒指，玉質溫潤，觸手生溫，是文\n"
            "人雅士喜愛的飾物。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "armor": 5,
        ]));
    }
    setup();
}
