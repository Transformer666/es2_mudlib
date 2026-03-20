// crocodile_god_armor.c

#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("鱷神鎧甲", ({"crocodile god armor", "crocodile_god_armor"}));
    set_weight(12000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "套");
        set("value", 400000);
        set("long",
            "一套以上古鱷神的鱗片鍛造的重甲，鎧甲表面佈滿了堅硬的鱗片，刀槍不入，散發著遠古的威壓。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "armor": 35,
        ]));
    }
    setup();
}
