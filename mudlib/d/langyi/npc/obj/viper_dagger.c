#include <weapon.h>

inherit F_DAGGER;

void create()
{
    set_name("毒蛇短匕", ({"viper_dagger", "dagger"}));
    set_weight(2000);
    setup_dagger(2, 8, 40, 3);

    if( !clonep() ) {
        set("wield_as", "dagger");
        set("unit", "把");
        set("value", 6000);
        set("rigidity", 25);
        set("long",
            "一把短匕﹐匕首上鑄有蛇形紋路﹐刃口泛著幽綠色的光芒﹐\n"
            "似乎塗有某種毒液。\n");
    }
    setup();
}
