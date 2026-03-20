// lengyu_sword.c

#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("冷玉寶劍", ({"lengyu sword", "lengyu_sword", "sword"}));
    set_weight(4000);
    setup_sword(3, 14, 80, 4);

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 200000);
        set("long",
            "一把以寒玉為鞘、精鋼為刃的寶劍，劍身泛著冰藍色的寒光，\n"
            "觸手生涼。\n");
    }
    setup();
}
