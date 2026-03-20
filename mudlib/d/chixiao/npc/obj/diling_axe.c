// diling_axe.c

#include <weapon.h>

inherit F_AXE;

void create()
{
    set_name("地靈雙手斧", ({"diling_axe", "diling axe", "axe"}));
    set_weight(20000);
    setup_axe(10, 60, 10, 3);

    if( !clonep() ) {
        set("wield_as", "axe");
        set("unit", "把");
        set("value", 400000);
        set("long",
            "一把沉重無比的巨型雙手斧，斧刃黝黑如墨，上面刻滿了古\n"
            "老的大地符文，乃是擊敗地靈後所得的神兵，蘊含大地之力。\n");
    }
    setup();
}
