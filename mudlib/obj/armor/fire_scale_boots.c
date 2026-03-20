// fire_scale_boots.c

#include <armor.h>

inherit F_FEET_EQ;

void create()
{
    set_name("火鱗靴", ({"fire scale boots", "fire_scale_boots", "boots"}));
    set_weight(1500);
    setup_feet_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("value", 240000);
        set("long",
            "一雙以火鱗片包覆的戰靴，靴面暗紅如炭火，踏地時發出沉穩\n"
            "的聲響，步履間隱約有火星飛濺。\n");
        set("wear_as", "feet_eq");
        set("apply_armor/feet_eq", ([
            "armor": 15,
        ]));
    }
    setup();
}
