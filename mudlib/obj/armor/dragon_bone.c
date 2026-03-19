// dragon_bone.c

#include <armor.h>

inherit F_WRIST_EQ;

void create()
{
    set_name("靈骨", ({"dragon_bone", "bone"}));
    set_weight(300);
    setup_wrist_eq();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 200000);
        set("long",
            "一塊遠古龍骨雕刻而成的腕飾，骨質溫潤如玉，佩戴時能感\n"
            "受到古龍的智慧在體內流淌，增進靈慧與悟性。\n");
        set("wear_as", "wrist_eq");
        set("apply_armor/wrist_eq", ([
            "armor": 5,
        ]));
    }
    setup();
}
