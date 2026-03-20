// iron_sword.c

#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("鐵劍", ({"iron_sword", "sword"}));
    set_weight(4000);
    setup_sword(2, 15, 4, 3);

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 5000);
        set("long",
            "一把尋常的鐵劍，雖然沒有什麼特殊之處，但打造得頗為\n"
            "紮實，適合行走江湖防身之用。\n");
    }
    setup();
}
