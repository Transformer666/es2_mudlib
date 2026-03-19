// dragon_armor.c

#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("怒龍錦冑", ({"dragon_armor", "armor"}));
    set_weight(25000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "套");
        set("value", 1000000);
        set("long",
            "一套雕刻著金龍圖紋的華麗鎧甲，沉重無比卻堅不可摧，據\n"
            "說乃是以龍鱗為範本鑄造，穿戴者刀槍不入。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "armor": 100,
        ]));
    }
    setup();
}
