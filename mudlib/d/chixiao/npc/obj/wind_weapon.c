// wind_weapon.c

#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("風神器", ({"wind_weapon", "wind blade", "blade"}));
    set_weight(3000);
    setup_blade(5, 40, 6, 3);

    if( !clonep() ) {
        set("wield_as", "blade");
        set("unit", "把");
        set("value", 80000);
        set("long",
            "一把輕若無物的彎刀，刀身泛著淡淡的青光，揮動時帶起陣\n"
            "陣勁風，據說是上古風神遺留在人間的神器之一。\n");
    }
    setup();
}
