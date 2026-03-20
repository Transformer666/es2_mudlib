// strange_copper_staff.c

#include <weapon.h>

inherit F_STAFF;

void create()
{
    set_name("玄烏杖", ({"strange copper staff", "strange_copper_staff", "staff"}));
    set_weight(6000);
    setup_staff(3, 22, 100, 6);

    if( !clonep() ) {
        set("wield_as", "staff");
        set("unit", "根");
        set("value", 160000);
        set("long",
            "一根烏黑的銅杖，杖頭雕刻著一隻展翅的玄鳥，杖身沉重而堅固，\n"
            "揮動時帶著一股肅殺之氣。\n");
    }
    setup();
}
