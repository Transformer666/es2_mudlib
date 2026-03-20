// zhenwu_blade.c

#include <weapon.h>

inherit F_BLADE;

void create()
{
    set_name("振武刀", ({"zhenwu_blade", "blade"}));
    set_weight(5000);
    setup_blade(4, 22, 5, 3);

    if( !clonep() ) {
        set("wield_as", "blade");
        set("unit", "把");
        set("value", 10000);
        set("long",
            "一把振武軍營制式戰刀，刀身厚重，刀柄以鯊魚皮纏繞，\n"
            "握感極佳，適合在戰場上長時間廝殺。\n");
    }
    setup();
}
