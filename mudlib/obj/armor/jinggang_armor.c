// jinggang_armor.c

#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("精鋼戰甲", ({"jinggang armor", "jinggang_armor", "armor"}));
    set_weight(15000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "套");
        set("value", 350000);
        set("long",
            "一套以精鋼鍛造的戰甲，甲片排列緊密，防禦力極佳，是軍營\n"
            "中高階將領的標準配備。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "armor": 35,
        ]));
    }
    setup();
}
