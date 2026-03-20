// wuzin_ring.c

#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("舞璃戒指", ({"wuzin ring", "wuzin_ring", "ring"}));
    set_weight(50);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 180000);
        set("long",
            "一枚璀璨的琉璃戒指，戒面鑲嵌著一顆微小的舞璃寶石，散發\n"
            "著柔和的光芒，據說能安定心神、增進悟性。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "armor": 3,
        ]));
    }
    setup();
}
