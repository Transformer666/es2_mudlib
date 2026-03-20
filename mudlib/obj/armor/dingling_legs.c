// dingling_legs.c

#include <armor.h>

inherit F_LEG_EQ;

void create()
{
    set_name("釘靈腿護", ({"dingling legs", "dingling_legs"}));
    set_weight(2000);
    setup_leg_eq();

    if( !clonep() ) {
        set("unit", "副");
        set("value", 280000);
        set("long",
            "一副以精鋼打造的腿甲，專為釘靈族的馬腿設計，堅固異常，奔跑時能增加衝擊力。\n");
        set("wear_as", "leg_eq");
        set("apply_armor/leg_eq", ([
            "armor": 25,
        ]));
    }
    setup();
}
