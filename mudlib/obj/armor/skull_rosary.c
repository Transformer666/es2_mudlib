// skull_rosary.c

#include <armor.h>

inherit F_NECK_EQ;

void create()
{
    set_name("白骨念珠", ({"skull_rosary", "rosary"}));
    set_weight(500);
    setup_neck_eq();

    if( !clonep() ) {
        set("unit", "串");
        set("value", 350000);
        set("long",
            "一串以骨骸雕刻而成的微型骷髏念珠，每顆珠子都散發著幽暗\n"
            "的力量，佩戴時能感受到一股陰寒之氣在體內流轉。\n");
        set("wear_as", "neck_eq");
        set("apply_armor/neck_eq", ([
            "armor": 25,
        ]));
    }
    setup();
}
