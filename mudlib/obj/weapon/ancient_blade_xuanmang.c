// ancient_blade_xuanmang.c

#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("古刃旋芒", ({"ancient blade xuanmang", "blade"}));
    set_weight(6000);
    setup_blade(4, 25, 115, 5);

    if( !clonep() ) {
        set("wield_as", "blade");
        set("unit", "把");
        set("value", 350000);
        set("long",
            "一把上古遺留的神兵，刀身散發著旋轉的光芒，揮動時刀氣四射，銳不可擋。\n");
    }
    setup();
}
