// qingfeng_blade.c

#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("清風刀", ({"qingfeng blade", "qingfeng_blade", "blade"}));
    set_weight(4500);
    setup_blade(4, 20, 90, 3);

    if( !clonep() ) {
        set("wield_as", "blade");
        set("unit", "把");
        set("value", 150000);
        set("long",
            "一把通體銀白的長刀，刀身輕薄如蟬翼，出刀時帶起一陣清風，\n"
            "令人心曠神怡。\n");
    }
    setup();
}
