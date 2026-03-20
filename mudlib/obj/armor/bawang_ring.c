// bawang_ring.c

#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("霸王指環", ({"bawang ring", "bawang_ring", "ring"}));
    set_weight(100);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 180000);
        set("long",
            "一枚以精銅鑄造的指環，環面刻有「霸」字，佩戴者攻勢大增。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "armor": 8,
        ]));
    }
    setup();
}
