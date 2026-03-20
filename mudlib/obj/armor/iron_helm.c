// iron_helm.c

#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
    set_name("鐵盔", ({"iron helm", "iron_helm", "helm"}));
    set_weight(2500);
    setup_head_eq();

    if( !clonep() ) {
        set("unit", "頂");
        set("value", 60000);
        set("long",
            "一頂普通的鐵盔，盔面厚實，能有效保護頭部，是軍中士兵的\n"
            "標準裝備。\n");
        set("wear_as", "head_eq");
        set("apply_armor/head_eq", ([
            "armor": 10,
        ]));
    }
    setup();
}
