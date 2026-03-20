// rain_weapon.c

#include <weapon.h>

inherit F_WHIP;

void create()
{
    set_name("雨神器", ({"rain_weapon", "rain whip", "whip"}));
    set_weight(2500);
    setup_whip(4, 25, 3, 6);

    if( !clonep() ) {
        set("wield_as", "whip");
        set("unit", "條");
        set("value", 80000);
        set("long",
            "一條水藍色的軟鞭，鞭身不斷滲出水珠，揮舞時如暴雨傾盆\n"
            "，據說是上古雨神遺留在人間的神器之一。\n");
    }
    setup();
}
