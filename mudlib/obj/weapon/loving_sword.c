// loving_sword.c

#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("歸心似劍", ({"loving sword", "loving_sword", "sword"}));
    set_weight(3000);
    setup_sword(3, 14, 90, 3);

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 200000);
        set("long",
            "一把纖細的長劍，劍身刻有「歸心」二字，劍鋒雖利但劍意卻透著\n"
            "一股溫柔，如歸人之心。\n");
    }
    setup();
}
