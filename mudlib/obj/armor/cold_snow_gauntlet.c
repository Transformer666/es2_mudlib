// cold_snow_gauntlet.c

#include <armor.h>

inherit F_HAND_EQ;

void create()
{
    set_name("冷雪手護", ({"cold snow gauntlet", "cold_snow_gauntlet"}));
    set_weight(600);
    setup_hand_eq();

    if( !clonep() ) {
        set("unit", "副");
        set("value", 180000);
        set("long",
            "一副以寒冰鍛造的護手，表面覆蓋著一層不化的冰晶，戴上後雙手寒氣逼人。\n");
        set("wear_as", "hand_eq");
        set("apply_armor/hand_eq", ([
            "armor": 15,
        ]));
    }
    setup();
}
