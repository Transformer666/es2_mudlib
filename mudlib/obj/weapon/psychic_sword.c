// psychic_sword.c

#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("靈通劍", ({"psychic_sword", "sword"}));
    set_weight(3500);
    setup_sword(2, 8, 60, 4);

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 180000);
        set("long",
            "一把通體透明的玉劍，劍身隱隱透出靈性的光輝，與持劍者\n"
            "心意相通，能感應周圍的靈力波動。\n");
    }
    setup();
}
