// celestial_bull_cane.c

#include <weapon.h>

inherit F_STAFF;

void create()
{
    set_name("饕餮法杖", ({"celestial bull cane", "celestial_bull_cane", "staff"}));
    set_weight(7000);
    setup_staff(3, 25, 130, 5);

    if( !clonep() ) {
        set("wield_as", "staff");
        set("unit", "根");
        set("value", 220000);
        set("long",
            "一根古老的法杖，杖頭雕刻著饕餮的頭顱，雙眼鑲嵌著血紅的寶石，\n"
            "散發著令人不安的氣息。\n");
    }
    setup();
}
