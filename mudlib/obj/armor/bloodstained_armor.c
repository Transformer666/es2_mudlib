// bloodstained_armor.c

#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("征衣血染", ({"bloodstained armor", "bloodstained_armor", "armor"}));
    set_weight(15000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "套");
        set("value", 500000);
        set("long",
            "一套染滿鮮血的戰甲，甲面上的血跡彷彿永遠無法洗淨，散發\n"
            "著濃烈的殺氣，乃八寶樓中征戰沙場的勇士遺物。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "armor": 55,
        ]));
    }
    setup();
}
