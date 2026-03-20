// symbol_of_dao.c

#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("邪骨指環", ({"symbol of dao", "symbol_of_dao", "ring"}));
    set_weight(80);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 250000);
        set("long",
            "一枚以邪骨雕刻而成的指環，環上刻有詭異的道家符文，在殘\n"
            "塔黑袍少年的屍身上發現，佩戴時能感受到一股邪氣護體。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "armor": 8,
        ]));
    }
    setup();
}
