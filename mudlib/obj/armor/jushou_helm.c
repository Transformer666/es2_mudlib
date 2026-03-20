// jushou_helm.c

#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
    set_name("狙首盔", ({"jushou helm", "jushou_helm", "helm"}));
    set_weight(1500);
    setup_head_eq();

    if( !clonep() ) {
        set("unit", "頂");
        set("value", 280000);
        set("long",
            "一頂以上古兇獸頭骨打造的頭盔，盔面猙獰可怖，佩戴者視野\n"
            "清明，能洞察敵人破綻。\n");
        set("wear_as", "head_eq");
        set("apply_armor/head_eq", ([
            "armor": 10,
        ]));
    }
    setup();
}
