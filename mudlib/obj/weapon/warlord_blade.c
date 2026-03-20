// warlord_blade.c

#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("戰神劈天刀", ({"warlord blade", "warlord_blade", "blade"}));
    set_weight(12000);
    setup_blade(8, 30, 180, 5);

    if( !clonep() ) {
        set("wield_as", "blade");
        set("unit", "把");
        set("value", 500000);
        set("long",
            "一把巨大的戰刀，刀身厚重如山，刀鋒閃耀著寒光，據說乃戰\n"
            "神所用之兵器，一刀劈下彷彿能開天闢地。\n");
    }
    setup();
}
