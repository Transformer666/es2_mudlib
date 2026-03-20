// dragon_boots.c

#include <armor.h>

inherit F_FEET_EQ;

void create()
{
    set_name("蛈蜇杳龍屐", ({"dragon boots", "dragon_boots"}));
    set_weight(1200);
    setup_feet_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("value", 300000);
        set("long",
            "一雙以龍鱗裝飾的戰靴，靴身堅固厚實卻不失靈活，穿上後行\n"
            "走如龍騰虎躍，攻守兼備。\n");
        set("wear_as", "feet_eq");
        set("apply_armor/feet_eq", ([
            "armor": 18,
        ]));
    }
    setup();
}
