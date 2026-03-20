// fire_scale_leggings.c

#include <armor.h>

inherit F_LEG_EQ;

void create()
{
    set_name("火鱗脛甲", ({"fire scale leggings", "fire_scale_leggings", "leggings"}));
    set_weight(4000);
    setup_leg_eq();

    if( !clonep() ) {
        set("unit", "副");
        set("value", 280000);
        set("long",
            "一副以火鱗片拼接而成的脛甲，覆蓋雙腿前方，暗紅的鱗片在\n"
            "光線下閃爍著火焰般的紋路。\n");
        set("wear_as", "leg_eq");
        set("apply_armor/leg_eq", ([
            "armor": 20,
        ]));
    }
    setup();
}
