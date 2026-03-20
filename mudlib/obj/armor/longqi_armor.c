// longqi_armor.c

#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("龍騎戰甲", ({"longqi armor", "longqi_armor", "armor"}));
    set_weight(20000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "套");
        set("value", 600000);
        set("long",
            "一套鑲嵌著龍鱗的重型戰甲，甲面雕刻著蟠龍圖騰，穿戴者\n"
            "宛若龍騎將軍，防禦力極為驚人。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "armor": 45,
        ]));
    }
    setup();
}
