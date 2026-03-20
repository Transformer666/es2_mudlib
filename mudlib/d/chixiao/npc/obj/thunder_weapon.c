// thunder_weapon.c

#include <weapon.h>

inherit F_STAFF;

void create()
{
    set_name("雷神器", ({"thunder_weapon", "thunder staff", "staff"}));
    set_weight(6000);
    setup_staff(6, 35, 4, 5);

    if( !clonep() ) {
        set("wield_as", "staff");
        set("unit", "根");
        set("value", 80000);
        set("long",
            "一根漆黑的金屬長棍，棍身纏繞著細微的電弧，握住時手掌\n"
            "微微發麻，據說是上古雷神遺留在人間的神器之一。\n");
    }
    setup();
}
