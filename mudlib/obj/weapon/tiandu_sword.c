// tiandu_sword.c

#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("天都劍", ({"tiandu sword", "sword"}));
    set_weight(4000);
    setup_sword(4, 14, 100, 4);

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 250000);
        set("long",
            "天都山鎮山之劍，劍身蘊含天地靈氣，劍光如虹，揮動時有仙風道骨之感。\n");
    }
    setup();
}
