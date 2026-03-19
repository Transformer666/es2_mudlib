#include <weapon.h>

inherit F_AXE;

void create()
{
    set_name("鍛造錘", ({"forge_hammer", "hammer"}));
    set_weight(10000);
    setup_axe(2, 10, 60, 1);

    if( !clonep() ) {
        set("wield_as", "axe");
        set("unit", "把");
        set("value", 3000);
        set("rigidity", 45);
        set("long",
            "一把沈重的鍛造錘﹐錘頭烏黑發亮﹐是鍛造匠不離手的工\n"
            "具﹐必要時也可用作武器。\n");
    }
    setup();
}
