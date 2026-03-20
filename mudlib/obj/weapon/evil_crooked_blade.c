// evil_crooked_blade.c

#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("邪門歪刀", ({"evil crooked blade", "blade"}));
    set_weight(5500);
    setup_blade(4, 24, 100, 4);

    if( !clonep() ) {
        set("wield_as", "blade");
        set("unit", "把");
        set("value", 160000);
        set("long",
            "一把造型怪異的彎刀，刀身歪斜扭曲，卻異常鋒利，刀鋒上殘留著暗紅的血漬。\n");
    }
    setup();
}
