#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("太乙劍", ({"taiyi_sword", "sword"}));
    set_weight(6000);
    setup_sword(2, 14, 45, 3);

    if( !clonep() ) {
        set("wield_as", ({"sword"}));
        set("unit", "把");
        set("value", 12000);
        set("rigidity", 35);
        set("long",
            "一把古樸的長劍﹐劍身上刻著太乙真符﹐劍氣流轉之間隱\n"
            "約可見道法符文的光芒。\n");
    }
    setup();
}
