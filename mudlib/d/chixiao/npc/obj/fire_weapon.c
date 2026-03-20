// fire_weapon.c

#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("火神器", ({"fire_weapon", "fire sword", "sword"}));
    set_weight(5000);
    setup_sword(5, 30, 6, 3);

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 80000);
        set("long",
            "一把通體赤紅的神秘長劍，劍身隱隱散發灼熱的氣息，據說\n"
            "是上古火神遺留在人間的神器之一，投入許願池可召喚天靈。\n");
    }
    setup();
}
