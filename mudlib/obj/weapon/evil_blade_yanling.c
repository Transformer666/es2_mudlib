// evil_blade_yanling.c

#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("邪刀焱靈", ({"evil blade yanling", "evil_blade_yanling", "blade"}));
    set_weight(6000);
    setup_blade(4, 18, 100, 4);

    if( !clonep() ) {
        set("wield_as", "blade");
        set("unit", "把");
        set("value", 350000);
        set("long",
            "一把散發著邪氣的彎刀，刀身上纏繞著幽暗的火焰紋路，揮動\n"
            "時隱約可見靈魂在刀鋒上哀嚎，乃八寶樓中的兇器。\n");
    }
    setup();
}
