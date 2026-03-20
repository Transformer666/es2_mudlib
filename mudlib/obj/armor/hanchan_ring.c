// hanchan_ring.c

#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("寒蟾指環", ({"hanchan ring", "hanchan_ring", "ring"}));
    set_weight(60);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 240000);
        set("long",
            "一枚寒氣逼人的指環，戒面雕刻著一隻蟾蜍，觸手冰涼，據說\n"
            "乃是以寒蟾之精血煉製，能增強冰系法術的威力。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "armor": 10,
        ]));
    }
    setup();
}
