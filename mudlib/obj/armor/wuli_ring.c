// wuli_ring.c

#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("舞璃戒指", ({"wuli ring", "wuli_ring"}));
    set_weight(40);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 160000);
        set("long",
            "一枚鑲嵌著七彩琉璃的戒指，光線照射下折射出絢麗的光芒，美得令人屏息。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "armor": 4,
        ]));
    }
    setup();
}
