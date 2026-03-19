// tiger_blade.c

#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("虎紋斬馬刀", ({"tiger_blade", "blade"}));
    set_weight(18000);
    setup_blade(4, 25, 200, 8);

    if( !clonep() ) {
        set("wield_as", "blade");
        set("unit", "把");
        set("value", 700000);
        set("long",
            "一把巨大無比的斬馬刀，刀身刻滿虎紋圖案，專為劈斬騎兵\n"
            "而鑄，重逾常刀數倍，非猛將不能揮舞。\n");
    }
    setup();
}
