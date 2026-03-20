// jibu_boots.c

#include <armor.h>

inherit F_FEET_EQ;

void create()
{
    set_name("疾步快靴", ({"jibu boots", "jibu_boots", "boots"}));
    set_weight(600);
    setup_feet_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("value", 320000);
        set("long",
            "一雙輕便的快靴，以上等鹿皮縫製，靴底嵌有風行符文，穿上\n"
            "後腳步輕盈如風，奔走如飛。\n");
        set("wear_as", "feet_eq");
        set("apply_armor/feet_eq", ([
            "armor": 25,
        ]));
    }
    setup();
}
