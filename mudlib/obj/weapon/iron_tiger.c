// iron_tiger.c

#include <weapon.h>

inherit F_DAGGER;

void create()
{
    set_name("鐵虎牙", ({"iron_tiger", "dagger"}));
    set_weight(2500);
    setup_dagger(3, 15, 90, 10);

    if( !clonep() ) {
        set("wield_as", "dagger");
        set("unit", "把");
        set("value", 200000);
        set("long",
            "一對以玄鐵鑄成的虎牙形匕首，刃如虎齒般彎曲鋒利，漆黑\n"
            "的刀身散發著冷冽的寒光。\n");
    }
    setup();
}
