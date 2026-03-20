// thunder_wolf_helm.c

#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
    set_name("雷火天狼罩", ({"thunder wolf helm", "thunder_wolf_helm"}));
    set_weight(1200);
    setup_head_eq();

    if( !clonep() ) {
        set("unit", "頂");
        set("value", 300000);
        set("long",
            "一頂以天狼骨為骨架打造的頭盔，盔頂雕刻著嘶吼的狼首，雷電環繞其上，威武不凡。\n");
        set("wear_as", "head_eq");
        set("apply_armor/head_eq", ([
            "armor": 18,
        ]));
    }
    setup();
}
