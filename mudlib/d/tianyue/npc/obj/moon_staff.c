// vim: syntax=lpc

#include <weapon.h>

inherit F_STAFF;

void create()
{
    set_name("月牙禪杖", ({"moon_staff", "staff"}));
    set_weight(7000);
    setup_staff(2, 11, 48, 2);

    if( !clonep() ) {
        set("wield_as", "staff");
        set("unit", "根");
        set("value", 7500);
        set("rigidity", 33);
        set("long",
            "一根白銅鑄成的禪杖﹐杖頭鑄成月牙形狀﹐鑲著七個銀環﹐\n"
            "行走時發出清脆的聲響。\n");
    }
    setup();
}
