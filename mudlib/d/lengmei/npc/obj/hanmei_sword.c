#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("寒梅劍", ({"hanmei_sword", "sword"}));
    set_weight(5000);
    setup_sword(2, 14, 42, 4);

    if( !clonep() ) {
        set("wield_as", ({"sword"}));
        set("unit", "把");
        set("value", 11000);
        set("rigidity", 30);
        set("long",
            "一把通體潔白的長劍﹐劍身上似有寒霜凝結﹐握在手中冰\n"
            "涼刺骨。這是冷梅莊的名劍之一。\n");
    }
    setup();
}
