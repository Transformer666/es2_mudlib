// xueyue_axe.c

#include <weapon.h>

inherit F_AXE;

void create()
{
    set_name("血月斧", ({"xueyue axe", "xueyue_axe", "axe"}));
    set_weight(8000);
    setup_axe(4, 18, 120, 3);

    if( !clonep() ) {
        set("wield_as", "axe");
        set("unit", "把");
        set("value", 280000);
        set("long",
            "一把泛著血紅色光芒的戰斧，斧刃如彎月，據說曾飲盡千人之\n"
            "血，每逢月圓之夜便會發出低沉的嗡鳴。\n");
    }
    setup();
}
