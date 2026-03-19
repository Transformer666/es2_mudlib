// dragon_needle.c

#include <weapon.h>

inherit F_NEEDLE;

void create()
{
    set_name("盤龍針", ({"dragon_needle", "needle"}));
    set_weight(500);
    setup_needle(3, 9, 60, 6);

    if( !clonep() ) {
        set("wield_as", "needle");
        set("unit", "枚");
        set("value", 200000);
        set("long",
            "一枚纖細的金針，針身刻有盤龍紋路，雖輕若無物，刺出時\n"
            "卻帶著深不可測的穿透之力。\n");
    }
    setup();
}
