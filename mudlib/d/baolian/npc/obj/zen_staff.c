#include <weapon.h>

inherit F_STAFF;

void create()
{
    set_name("禪杖", ({"zen_staff", "staff"}));
    set_weight(8000);
    setup_staff(2, 12, 50, 2);

    if( !clonep() ) {
        set("wield_as", "staff");
        set("unit", "根");
        set("value", 8000);
        set("rigidity", 35);
        set("long",
            "一根精鐵鑄成的禪杖﹐杖頭鑲著九個銅環﹐行走時發出叮\n"
            "叮噹噹的聲響﹐頗具佛門威嚴。\n");
    }
    setup();
}
