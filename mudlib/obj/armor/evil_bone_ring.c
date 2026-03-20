// evil_bone_ring.c

#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("邪骨指環", ({"evil bone ring", "evil_bone_ring"}));
    set_weight(60);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 180000);
        set("long",
            "一枚以魔物骨骸雕刻而成的戒指，散發著邪異的氣息，佩戴時指尖會泛起暗紫色的光。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "armor": 5,
        ]));
    }
    setup();
}
