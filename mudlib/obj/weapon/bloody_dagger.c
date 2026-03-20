// bloody_dagger.c

#include <weapon.h>

inherit F_DAGGER;

void create()
{
    set_name("血匕封喉", ({"bloody dagger", "bloody_dagger", "dagger"}));
    set_weight(500);
    setup_dagger(4, 14, 70, 2);

    if( !clonep() ) {
        set("wield_as", "dagger");
        set("unit", "把");
        set("value", 280000);
        set("long",
            "一把殺氣凜然的短匕，匕身隱約泛著血紅光芒，刃鋒極薄，一\n"
            "擊致命，專取敵人咽喉要害。\n");
    }
    setup();
}
