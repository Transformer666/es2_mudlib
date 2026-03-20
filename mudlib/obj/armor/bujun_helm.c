// bujun_helm.c

#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
    set_name("步軍戰盔", ({"bujun helm", "bujun_helm", "helm"}));
    set_weight(2000);
    setup_head_eq();

    if( !clonep() ) {
        set("unit", "頂");
        set("value", 80000);
        set("long",
            "一頂步軍制式戰盔，以鐵皮鑲嵌，盔頂飾有紅纓，是步兵將\n"
            "士的標準裝備。\n");
        set("wear_as", "head_eq");
        set("apply_armor/head_eq", ([
            "armor": 12,
        ]));
    }
    setup();
}
