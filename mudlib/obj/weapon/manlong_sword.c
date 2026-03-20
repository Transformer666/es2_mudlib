// manlong_sword.c

#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("蠻龍", ({"manlong sword", "manlong_sword", "sword"}));
    set_weight(14000);
    setup_sword(5, 20, 150, 5);

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 800000);
        set("long",
            "一把巨大的蠻龍劍，劍身寬如門板，散發著暴戾的龍氣，需\n"
            "雙手方能勉強持握，一劍揮出便有排山倒海之勢。\n");
    }
    setup();
}
