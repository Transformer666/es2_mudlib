// woochan_ring.c

#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("無腸寶珠", ({"woochan ring", "woochan_ring"}));
    set_weight(50);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 300000);
        set("long",
            "一枚散發著靈光的寶珠戒指，乃無腸族的傳族之寶，能引導體內氣脈運行，加速恢復。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "armor": 8,
        ]));
    }
    setup();
}
