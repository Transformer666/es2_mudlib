// military_armor.c

#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("衛國軍甲", ({"military_armor", "armor"}));
    set_weight(12000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "套");
        set("value", 20000);
        set("long",
            "一套衛國軍制式鎧甲，以鐵片層疊鉚接而成，雖然沉重\n"
            "卻能有效防禦刀劍劈砍，是衛國守軍的標準防具。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "armor": 8,
        ]));
    }
    setup();
}
