// erotic_staff.c

#include <weapon.h>

inherit F_STAFF;

void create()
{
    set_name("交歡杖", ({"erotic_staff", "staff"}));
    set_weight(8000);
    setup_staff(3, 16, 200, 5);

    if( !clonep() ) {
        set("wield_as", "staff");
        set("unit", "根");
        set("value", 400000);
        set("long",
            "一根雕工精美的奇杖，杖身交替散發著灼熱與冰寒的氣息，據\n"
            "說此杖蘊含陰陽交濟之力，能調和天地元氣。\n");
    }
    setup();
}
