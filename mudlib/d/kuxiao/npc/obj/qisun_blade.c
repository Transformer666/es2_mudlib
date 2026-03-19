#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("七損刀", ({"qisun_blade", "blade"}));
    set_weight(6000);
    setup_blade(2, 12, 50, 2);

    if( !clonep() ) {
        set("wield_as", "blade");
        set("unit", "把");
        set("value", 8000);
        set("rigidity", 30);
        set("long",
            "一把造型詭異的長刀﹐刀身上刻著七道裂紋﹐據說這七道裂\n"
            "紋代表著人生的七種苦難。\n");
    }
    setup();
}
