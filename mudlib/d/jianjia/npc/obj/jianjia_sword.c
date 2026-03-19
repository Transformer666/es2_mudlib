#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("劍甲劍", ({"jianjia_sword", "sword"}));
    set_weight(6000);
    setup_sword(2, 14, 48, 3);

    if( !clonep() ) {
        set("wield_as", ({"sword"}));
        set("unit", "把");
        set("value", 10000);
        set("rigidity", 40);
        set("long",
            "一把劍甲門鍛造的精鋼長劍﹐劍身上刻著火焰紋路﹐握在\n"
            "手中微微發燙﹐可見鑄劍之時灌注了大量的心血。\n");
    }
    setup();
}
