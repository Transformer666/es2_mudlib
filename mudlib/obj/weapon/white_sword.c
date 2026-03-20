// white_sword.c

#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("白色長劍", ({"white sword", "white_sword", "sword"}));
    set_weight(3500);
    setup_sword(3, 12, 80, 4);

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 120000);
        set("long",
            "一把通體雪白的長劍，劍身純淨無瑕，散發著淡淡的光輝，\n"
            "是一把品質上乘的好劍。\n");
    }
    setup();
}
