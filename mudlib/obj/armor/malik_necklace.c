// malik_necklace.c

#include <armor.h>

inherit F_NECK_EQ;

void create()
{
    set_name("巫首項鍊", ({"malik necklace", "malik_necklace"}));
    set_weight(300);
    setup_neck_eq();

    if( !clonep() ) {
        set("unit", "條");
        set("value", 200000);
        set("long",
            "一條以巫族秘法祝聖的項鍊，墜飾是一顆散發著幽綠光芒的靈石，蘊含著神秘的巫術之力。\n");
        set("wear_as", "neck_eq");
        set("apply_armor/neck_eq", ([
            "armor": 15,
        ]));
    }
    setup();
}
