// yiluo_greatsword.c

#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("易羅大劍", ({"yiluo greatsword", "sword"}));
    set_weight(8000);
    setup_sword(5, 20, 150, 5);

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 320000);
        set("long",
            "一把巨大的闊劍，劍身厚重寬闊，刻有古老的符文，需要極大的膂力方能揮動，一擊之下地動山搖。\n");
    }
    setup();
}
