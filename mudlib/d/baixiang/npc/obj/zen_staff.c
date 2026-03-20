// zen_staff.c

#include <weapon.h>

inherit F_STAFF;

void create()
{
    set_name("禪杖", ({"zen_staff", "staff"}));
    set_weight(6000);
    setup_staff(3, 20, 4, 5);

    if( !clonep() ) {
        set("wield_as", "staff");
        set("unit", "根");
        set("value", 8000);
        set("long",
            "一根以精鋼打造的禪杖，杖頭套著九個銅環，行走時\n"
            "環環相叩，發出清脆的聲響，乃是白象寺僧人的隨身法器。\n");
    }
    setup();
}
