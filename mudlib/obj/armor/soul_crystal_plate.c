// soul_crystal_plate.c

#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("靈中樞甲", ({"soul_crystal_plate", "armor"}));
    set_weight(15000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "套");
        set("value", 200000);
        set("long",
            "一套由神秘水晶鑄成的鎧甲，甲身不斷閃爍著內蘊的光芒，\n"
            "彷彿有靈魂在其中脈動，能增強穿戴者的靈力感知。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "armor": 30,
        ]));
    }
    setup();
}
