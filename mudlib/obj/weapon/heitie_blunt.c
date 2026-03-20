// heitie_blunt.c

#include <weapon.h>

inherit F_BLUNT;

void create()
{
    set_name("黑鐵大槌", ({"heitie blunt", "heitie_blunt", "hammer"}));
    set_weight(18000);
    setup_blunt(6, 15, 250, 4);

    if( !clonep() ) {
        set("wield_as", "blunt");
        set("unit", "把");
        set("value", 600000);
        set("long",
            "一把以玄鐵鍛造的巨型大槌，通體漆黑，沉重無比，需雙手方\n"
            "能舉起，一槌之力可震碎巨石。\n");
    }
    setup();
}
