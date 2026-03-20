// jade_pendant.c

#include <armor.h>

inherit F_WAIST_EQ;

void create()
{
    set_name("白玉腰佩", ({"jade_pendant", "pendant"}));
    set_weight(200);
    setup_waist_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 8000);
        set("long",
            "一枚以羊脂白玉雕刻而成的腰佩，玉質溫潤，雕工精細，\n"
            "是京畿官員常佩戴的飾物，象徵著身份與品味。\n");
        set("wear_as", "waist_eq");
        set("apply_armor/waist_eq", ([
            "armor": 1,
        ]));
    }
    setup();
}
