// silky_gloves.c

#include <armor.h>

inherit F_HAND_EQ;

void create()
{
    set_name("青絲手套", ({"silky gloves", "silky_gloves", "gloves"}));
    set_weight(300);
    setup_hand_eq();

    if( !clonep() ) {
        set("unit", "副");
        set("value", 200000);
        set("long",
            "一副以青絲編織的手套，觸感柔滑卻異常堅韌，戴上後指間靈\n"
            "活自如，有助於施展法術和暗器。\n");
        set("wear_as", "hand_eq");
        set("apply_armor/hand_eq", ([
            "armor": 12,
        ]));
    }
    setup();
}
