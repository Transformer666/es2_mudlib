// bujun_armor.c

#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("步軍戰鎧", ({"bujun armor", "bujun_armor", "armor"}));
    set_weight(14000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "套");
        set("value", 180000);
        set("long",
            "一套步軍制式戰鎧，甲片層疊，防護嚴密，是步兵部隊的標準\n"
            "重裝。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "armor": 28,
        ]));
    }
    setup();
}
