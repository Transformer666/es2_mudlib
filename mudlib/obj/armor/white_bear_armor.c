// white_bear_armor.c

#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("白熊護甲", ({"white bear armor", "white_bear_armor"}));
    set_weight(10000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "套");
        set("value", 380000);
        set("long",
            "一套以白熊皮毛和骨骼打造的護甲，厚重保暖，能抵禦極寒侵襲，同時堅固異常。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "armor": 30,
        ]));
    }
    setup();
}
