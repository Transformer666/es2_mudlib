// qingbu_robe.c

#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("青布官服", ({"qingbu robe", "qingbu_robe", "cloth"}));
    set_weight(2000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 60000);
        set("long",
            "一件青色的官服，布料雖然樸素，但剪裁得體，是低階官員的\n"
            "日常穿著。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 5,
        ]));
    }
    setup();
}
