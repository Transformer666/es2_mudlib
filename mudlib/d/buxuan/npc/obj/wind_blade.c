#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("逐風刃", ({"wind_blade", "sword"}));
    set_weight(5000);
    setup_sword(2, 13, 40, 4);

    if( !clonep() ) {
        set("wield_as", ({"sword"}));
        set("unit", "把");
        set("value", 10000);
        set("rigidity", 30);
        set("long",
            "一把輕巧的文士劍﹐劍身窄而薄﹐揮動時似有風聲呼嘯。\n");
    }
    setup();
}
