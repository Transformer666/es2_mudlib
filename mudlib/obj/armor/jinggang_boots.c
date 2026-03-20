// jinggang_boots.c

#include <armor.h>

inherit F_FEET_EQ;

void create()
{
    set_name("精鋼戰靴", ({"jinggang boots", "jinggang_boots", "boots"}));
    set_weight(3000);
    setup_feet_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("value", 150000);
        set("long",
            "一雙以精鋼打造的戰靴，靴面包覆著鋼片，堅固耐用，是軍中\n"
            "將士的標配。\n");
        set("wear_as", "feet_eq");
        set("apply_armor/feet_eq", ([
            "armor": 15,
        ]));
    }
    setup();
}
