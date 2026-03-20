// zaobu_boots.c

#include <armor.h>

inherit F_FEET_EQ;

void create()
{
    set_name("皂步靴", ({"zaobu boots", "zaobu_boots", "boots"}));
    set_weight(1500);
    setup_feet_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("value", 50000);
        set("long",
            "一雙黑色的軍用步靴，靴底厚實耐磨，適合長途行軍。\n");
        set("wear_as", "feet_eq");
        set("apply_armor/feet_eq", ([
            "armor": 8,
        ]));
    }
    setup();
}
