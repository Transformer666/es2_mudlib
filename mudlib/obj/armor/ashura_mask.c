// ashura_mask.c

#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
    set_name("修羅之面", ({"ashura mask", "ashura_mask"}));
    set_weight(500);
    setup_head_eq();

    if( !clonep() ) {
        set("unit", "副");
        set("value", 250000);
        set("long",
            "一副奇異的面具，一半猙獰醜陋，一半妖豔美麗，戴上後彷彿能看透人心的善惡。\n");
        set("wear_as", "head_eq");
        set("apply_armor/head_eq", ([
            "armor": 10,
        ]));
    }
    setup();
}
