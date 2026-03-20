// snow_soul_dagger.c

#include <weapon.h>

inherit F_DAGGER;

void create()
{
    set_name("雪魂匕", ({"snow soul dagger", "dagger"}));
    set_weight(800);
    setup_dagger(3, 12, 60, 2);

    if( !clonep() ) {
        set("wield_as", "dagger");
        set("unit", "把");
        set("value", 150000);
        set("long",
            "一把以寒冰精華鍛造的短匕，匕身透明如雪，刺入敵人體內時會釋放出刺骨寒氣。\n");
    }
    setup();
}
