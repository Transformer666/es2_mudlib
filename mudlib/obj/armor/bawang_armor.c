// bawang_armor.c

#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("霸王鎧", ({"bawang armor", "bawang_armor", "armor"}));
    set_weight(18000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "套");
        set("value", 500000);
        set("long",
            "一套沉重的霸王鎧甲，以精鋼鑄造，甲面雕刻著猛虎吞日的\n"
            "圖紋，穿戴者彷彿化身為戰場上的霸王。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "armor": 45,
        ]));
    }
    setup();
}
