// medicine_king_sword.c

#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("藥王神劍", ({"medicine king sword", "medicine_king_sword", "sword"}));
    set_weight(4000);
    setup_sword(4, 16, 120, 4);

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 380000);
        set("long",
            "藥王谷鎮谷之寶，劍身散發著淡淡藥香，不僅鋒利無比，\n"
            "更能以劍氣化為治癒之力。\n");
    }
    setup();
}
