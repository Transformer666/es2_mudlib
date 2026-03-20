// guard_blade.c

#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("官刀", ({"guard_blade", "blade"}));
    set_weight(5000);
    setup_blade(3, 22, 4, 3);

    if( !clonep() ) {
        set("wield_as", "blade");
        set("unit", "把");
        set("value", 10000);
        set("long",
            "一把朝廷制式官刀，刀身微彎，刀柄以黃銅包裹，刀鞘\n"
            "漆成朱紅色，乃是京畿衙門差役的標配武器。\n");
    }
    setup();
}
