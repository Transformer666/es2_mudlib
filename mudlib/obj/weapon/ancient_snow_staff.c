// ancient_snow_staff.c

#include <weapon.h>

inherit F_STAFF;

void create()
{
    set_name("萬年雪", ({"ancient snow staff", "ancient_snow_staff", "staff"}));
    set_weight(4000);
    setup_staff(2, 25, 120, 5);

    if( !clonep() ) {
        set("wield_as", "staff");
        set("unit", "根");
        set("value", 350000);
        set("long",
            "一根以萬年寒冰凝結而成的法杖，通體透明如冰晶，握在手中寒意徹骨，\n"
            "揮動時冰雪紛飛。\n");
    }
    setup();
}
