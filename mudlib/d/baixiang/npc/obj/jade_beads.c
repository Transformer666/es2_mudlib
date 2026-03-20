// jade_beads.c

#include <armor.h>

inherit F_NECK_EQ;

void create()
{
    set_name("翠玉佛珠", ({"jade_beads", "beads"}));
    set_weight(300);
    setup_neck_eq();

    if( !clonep() ) {
        set("unit", "串");
        set("value", 6000);
        set("long",
            "一串以翠玉打磨而成的佛珠，共一百零八顆，顆顆晶瑩\n"
            "剔透，持之誦經有靜心凝神之效。\n");
        set("wear_as", "neck_eq");
        set("apply_armor/neck_eq", ([
            "armor": 2,
        ]));
    }
    setup();
}
