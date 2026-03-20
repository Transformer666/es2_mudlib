// goddess_sword.c

#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("西山仙劍", ({"goddess sword", "goddess_sword", "sword"}));
    set_weight(5000);
    setup_sword(5, 16, 120, 5);

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 400000);
        set("long",
            "一把仙氣繚繞的寶劍，劍身銀白如月，據說鑄於西山仙境之中，\n"
            "需戰場聲望五十以上的勇士方能購得。\n");
    }
    setup();
}
