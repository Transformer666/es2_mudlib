// dragon_feather.c

#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("龍思羽", ({"dragon feather", "dragon_feather"}));
    set_weight(1000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 350000);
        set("long",
            "一件以龍族羽翼編織而成的輕甲，輕若鴻毛卻堅韌無比，穿著時隱隱有龍吟之聲。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 18,
        ]));
    }
    setup();
}
