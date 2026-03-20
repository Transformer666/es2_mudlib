// diling_heart.c

#include <armor.h>

inherit F_NECK_EQ;

void create()
{
    set_name("地靈心", ({"diling_heart", "diling heart", "heart"}));
    set_weight(800);
    setup_neck_eq();

    if( !clonep() ) {
        set("unit", "顆");
        set("value", 500000);
        set("long",
            "一顆沉甸甸的褐色寶石，表面佈滿泥土般的紋路，內部隱約\n"
            "可見脈動的光芒，乃是地靈的核心，蘊含著大地的生命之力。\n");
        set("wear_as", "neck_eq");
        set("apply_armor/neck_eq", ([
            "armor": 6,
        ]));
    }
    setup();
}
