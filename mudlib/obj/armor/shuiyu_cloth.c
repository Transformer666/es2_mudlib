// shuiyu_cloth.c

#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("水慾羽衣", ({"shuiyu cloth", "shuiyu_cloth", "cloth"}));
    set_weight(1200);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 380000);
        set("long",
            "一件以珍稀水禽羽毛織就的輕衣，通體泛著水光，穿著時宛若\n"
            "身披流水，能大幅提升警覺與攻擊能力。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 15,
        ]));
    }
    setup();
}
