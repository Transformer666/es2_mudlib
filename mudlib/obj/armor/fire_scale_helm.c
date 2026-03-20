// fire_scale_helm.c

#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
    set_name("火鱗盔", ({"fire scale helm", "fire_scale_helm", "helm"}));
    set_weight(2000);
    setup_head_eq();

    if( !clonep() ) {
        set("unit", "頂");
        set("value", 260000);
        set("long",
            "一頂以火鱗片鍛造的頭盔，盔頂雕刻著火焰紋飾，戴上後額前\n"
            "的火鱗片微微發光，彷彿注視著前方的敵人。\n");
        set("wear_as", "head_eq");
        set("apply_armor/head_eq", ([
            "armor": 18,
        ]));
    }
    setup();
}
