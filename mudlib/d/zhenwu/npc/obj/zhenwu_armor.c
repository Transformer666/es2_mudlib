// zhenwu_armor.c

#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("振武軍甲", ({"zhenwu_armor", "armor"}));
    set_weight(13000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "套");
        set("value", 25000);
        set("long",
            "一套振武軍營的制式鎧甲，甲片精鍛，胸甲上刻有「振武」\n"
            "二字，比一般軍甲更為精良，是振武營將士的榮耀象徵。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "armor": 10,
        ]));
    }
    setup();
}
