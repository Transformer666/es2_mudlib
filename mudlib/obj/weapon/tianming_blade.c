// tianming_blade.c

#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("天命刃", ({"tianming blade", "blade"}));
    set_weight(5000);
    setup_blade(4, 25, 110, 4);

    if( !clonep() ) {
        set("wield_as", "blade");
        set("unit", "把");
        set("value", 280000);
        set("long",
            "一把散發著命運氣息的長刀，刀身上刻著「天命」二字，據說此刀能斬斷因果，改寫命運。\n");
    }
    setup();
}
