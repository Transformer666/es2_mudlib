// mietianjian.c

#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("蔑天劍", ({"mietianjian", "sword"}));
    set_weight(6000);
    setup_sword(5, 18, 140, 7);

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 500000);
        set("long",
            "一把泛著金色光芒的傳奇寶劍，劍身隱隱發出靈力共鳴的嗡鳴\n"
            "聲，據說此劍曾斬落天上星辰，故名蔑天。\n");
    }
    setup();
}
