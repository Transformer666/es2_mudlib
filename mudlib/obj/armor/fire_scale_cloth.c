// fire_scale_cloth.c

#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("火鱗衣", ({"fire scale cloth", "fire_scale_cloth", "cloth"}));
    set_weight(3000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 300000);
        set("long",
            "一件以火鱗絲線編織的內衣，穿在鎧甲之內，能吸收火焰傷害，\n"
            "同時為穿戴者提供額外的防護。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 25,
        ]));
    }
    setup();
}
