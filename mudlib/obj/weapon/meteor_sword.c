// meteor_sword.c

#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("追月流星劍", ({"meteor sword", "sword"}));
    set_weight(3500);
    setup_sword(5, 16, 130, 4);

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 300000);
        set("long",
            "一把銀白的長劍，劍身如流星般閃耀，出劍時劍光如追月流星，劃破長空，令人目眩。\n");
    }
    setup();
}
