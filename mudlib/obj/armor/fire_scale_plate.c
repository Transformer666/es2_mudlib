// fire_scale_plate.c

#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("火鱗胸鎧", ({"fire scale plate", "fire_scale_plate", "armor"}));
    set_weight(10000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "套");
        set("value", 450000);
        set("long",
            "一套以火鱗鑄造的胸甲，甲面泛著暗紅色的光澤，觸手微燙，\n"
            "乃火鱗套裝的核心部件，與蔑天劍同源。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "armor": 45,
        ]));
    }
    setup();
}
