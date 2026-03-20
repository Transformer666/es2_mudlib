// copper_helm.c

#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
    set_name("銅盔", ({"copper helm", "copper_helm", "helm"}));
    set_weight(1800);
    setup_head_eq();

    if( !clonep() ) {
        set("unit", "頂");
        set("value", 40000);
        set("long",
            "一頂以青銅鑄造的頭盔，雖然略顯笨重，但防護效果不錯。\n");
        set("wear_as", "head_eq");
        set("apply_armor/head_eq", ([
            "armor": 8,
        ]));
    }
    setup();
}
