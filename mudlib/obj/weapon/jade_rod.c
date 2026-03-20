// jade_rod.c

#include <weapon.h>

inherit F_STAFF;

void create()
{
    set_name("寒玉藥杵", ({"jade rod", "jade_rod", "staff"}));
    set_weight(5000);
    setup_staff(3, 20, 120, 5);

    if( !clonep() ) {
        set("wield_as", "staff");
        set("unit", "根");
        set("value", 180000);
        set("long",
            "以千年寒玉雕琢而成的藥杵，通體晶瑩剔透，散發著淡淡寒氣，\n"
            "既是煉藥之器，亦可作為防身之用。\n");
    }
    setup();
}
