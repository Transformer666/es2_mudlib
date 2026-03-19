// equalizer.c

#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("毒刀「胡惑」", ({"equalizer", "blade"}));
    set_weight(8000);
    setup_blade(4, 20, 180, 8);

    if( !clonep() ) {
        set("wield_as", "blade");
        set("unit", "把");
        set("value", 500000);
        set("long",
            "一把弧度詭異的彎刀，刀身不斷滲出毒液，名為「胡惑」，\n"
            "意指中此刀者必將神智恍惚，生死難料。\n");
    }
    setup();
}
