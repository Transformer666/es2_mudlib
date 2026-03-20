// military_pike.c

#include <weapon.h>

inherit F_PIKE;

void create()
{
    set_name("軍用長槍", ({"military_pike", "pike"}));
    set_weight(7000);
    setup_pike(4, 28, 5, 5);

    if( !clonep() ) {
        set("wield_as", "pike");
        set("unit", "把");
        set("value", 12000);
        set("long",
            "一把衛國軍制式長槍，槍桿以白蠟木製成，槍頭為精鋼\n"
            "打造，鋒利無比，是衛國守軍的標準裝備。\n");
    }
    setup();
}
