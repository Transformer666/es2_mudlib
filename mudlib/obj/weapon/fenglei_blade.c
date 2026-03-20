// fenglei_blade.c

#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("風雷刀", ({"fenglei blade", "blade"}));
    set_weight(5500);
    setup_blade(4, 24, 105, 4);

    if( !clonep() ) {
        set("wield_as", "blade");
        set("unit", "把");
        set("value", 300000);
        set("long",
            "一把蘊含風雷之力的寶刀，刀身電光閃爍，出刀時風雷大作，威勢驚人。\n");
    }
    setup();
}
