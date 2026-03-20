// blue_saliva_blade.c

#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("藍涎刀", ({"blue saliva blade", "blue_saliva_blade", "blade"}));
    set_weight(5000);
    setup_blade(4, 22, 95, 3);

    if( !clonep() ) {
        set("wield_as", "blade");
        set("unit", "把");
        set("value", 180000);
        set("long",
            "一把泛著藍光的彎刀，刀身滲出藍色的毒液，被此刀所傷者，\n"
            "傷口會迅速麻痺。\n");
    }
    setup();
}
