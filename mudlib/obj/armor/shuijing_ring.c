// shuijing_ring.c

#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("水晶戒指", ({"shuijing ring", "shuijing_ring", "ring"}));
    set_weight(20);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 80000);
        set("long",
            "一枚晶瑩剔透的水晶戒指，在陽光下折射出七彩光芒，美麗\n"
            "動人。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "armor": 3,
        ]));
    }
    setup();
}
