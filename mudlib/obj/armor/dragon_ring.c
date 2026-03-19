// dragon_ring.c

#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("龍戒", ({"dragon_ring", "ring"}));
    set_weight(100);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 400000);
        set("long",
            "一枚漆黑的戒指，戒面雕刻著栩栩如生的微型龍紋，細看之\n"
            "下那些龍紋似乎在緩緩遊動，令人心生敬畏。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "armor": 5,
        ]));
    }
    setup();
}
