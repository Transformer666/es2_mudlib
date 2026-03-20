// coldblood_dagger.c

#include <weapon.h>

inherit F_DAGGER;

void create()
{
    set_name("無情匕", ({"coldblood dagger", "coldblood_dagger", "dagger"}));
    set_weight(600);
    setup_dagger(5, 16, 80, 2);

    if( !clonep() ) {
        set("wield_as", "dagger");
        set("unit", "把");
        set("value", 300000);
        set("long",
            "一把冷冽無情的短匕，匕身泛著冰冷的金屬光澤，專為背刺而\n"
            "設計，出手必殺，絕不留情。\n");
    }
    setup();
}
