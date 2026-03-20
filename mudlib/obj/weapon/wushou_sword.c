// wushou_sword.c

#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("巫首劍", ({"wushou sword", "wushou_sword", "sword"}));
    set_weight(4500);
    setup_sword(4, 16, 90, 4);

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 250000);
        set("long",
            "一把巫首族祖傳的神秘寶劍，劍身刻有古老的巫術符文，散發\n"
            "著詭異的靈光。\n");
    }
    setup();
}
