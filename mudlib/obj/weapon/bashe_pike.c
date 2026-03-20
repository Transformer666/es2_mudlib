// bashe_pike.c

#include <weapon.h>

inherit F_PIKE;

void create()
{
    set_name("巴蛇大矛", ({"bashe pike", "bashe_pike", "pike"}));
    set_weight(10000);
    setup_pike(5, 20, 90, 8);

    if( !clonep() ) {
        set("wield_as", "pike");
        set("unit", "把");
        set("value", 480000);
        set("long",
            "一桿以巴蛇脊骨為杆、蛇牙為尖的長矛，矛身佈滿蛇鱗紋路，\n"
            "刺出時帶著一股令人膽寒的腥風。\n");
    }
    setup();
}
