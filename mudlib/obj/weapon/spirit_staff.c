// spirit_staff.c

#include <weapon.h>

inherit F_STAFF;

void create()
{
    set_name("聖靈禪杖", ({"cane of spirit", "spirit_staff", "staff"}));
    set_weight(7000);
    setup_staff(5, 22, 120, 7);

    if( !clonep() ) {
        set("wield_as", "staff");
        set("unit", "根");
        set("value", 400000);
        set("long",
            "一根散發聖光的禪杖，杖身以千年古木製成，頂端鑲嵌著一顆\n"
            "發光的靈石，揮動時有梵音陣陣，能驅邪鎮魔。\n");
    }
    setup();
}
