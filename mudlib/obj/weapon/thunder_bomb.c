// thunder_bomb.c

#include <weapon.h>

inherit F_BLUNT;

void create()
{
    set_name("霹靂雷火彈", ({"thunder_bomb", "thunder bomb", "bomb"}));
    set_weight(2000);
    setup_blunt(5, 35, 6, 2);

    if( !clonep() ) {
        set("wield_as", "blunt");
        set("unit", "顆");
        set("value", 200000);
        set("long",
            "一顆拳頭大小的黑色鐵球，表面刻滿了雷紋，內部封印著霹靂\n"
            "雷火之力。搖晃時能聽到裡面雷電翻滾的聲音，使用時威力\n"
            "驚人，方圓數丈之內皆受其殃。\n");
    }
    setup();
}
