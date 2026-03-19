#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("暗影刀", ({"dark_blade", "blade"}));
    set_weight(5000);
    setup_blade(2, 12, 55, 2);

    if( !clonep() ) {
        set("wield_as", "blade");
        set("unit", "把");
        set("value", 8000);
        set("rigidity", 30);
        set("long",
            "一把通體漆黑的長刀﹐刀身不反光﹐非常適合夜間行動。\n"
            "刀刃鋒利無比﹐隱隱透著一股寒氣。\n");
    }
    setup();
}
