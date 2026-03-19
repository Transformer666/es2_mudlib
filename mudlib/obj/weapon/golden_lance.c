// golden_lance.c

#include <weapon.h>

inherit F_PIKE;

void create()
{
    set_name("金龍豹紋槍", ({"golden_lance", "lance", "pike"}));
    set_weight(15000);
    setup_pike(5, 18, 95, 14);

    if( !clonep() ) {
        set("wield_as", "pike");
        set("unit", "把");
        set("value", 600000);
        set("long",
            "一柄巨大的長槍，槍身刻滿金龍與豹紋圖案，沉重無比，非\n"
            "力大之人難以駕馭，傳說乃是古代戰神的愛槍。\n");
    }
    setup();
}
