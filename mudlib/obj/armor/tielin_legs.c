// tielin_legs.c

#include <armor.h>

inherit F_LEG_EQ;

void create()
{
    set_name("鐵鱗腿護", ({"tielin legs", "tielin_legs", "legs"}));
    set_weight(2500);
    setup_leg_eq();

    if( !clonep() ) {
        set("unit", "副");
        set("value", 120000);
        set("long",
            "一副以鐵鱗片拼接而成的腿護，覆蓋大腿至膝蓋，能有效保護\n"
            "下肢要害。\n");
        set("wear_as", "leg_eq");
        set("apply_armor/leg_eq", ([
            "armor": 15,
        ]));
    }
    setup();
}
