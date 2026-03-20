// zuiya_dagger.c

#include <weapon.h>

inherit F_DAGGER;

void create()
{
    set_name("罪牙匕", ({"zuiya dagger", "zuiya_dagger", "dagger"}));
    set_weight(1500);
    setup_dagger(3, 18, 85, 2);

    if( !clonep() ) {
        set("wield_as", "dagger");
        set("unit", "把");
        set("value", 450000);
        set("long",
            "一把以上古兇獸饕餮的獠牙雕鑄而成的匕首，匕身彎曲如獸牙，\n"
            "刃口處滲出絲絲黑氣，傳說被此匕刺中者內力盡失。\n");
    }
    setup();
}
