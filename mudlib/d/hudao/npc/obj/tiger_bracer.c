// tiger_bracer.c

#include <armor.h>

inherit F_WRIST_EQ;

void create()
{
    set_name("虎紋護腕", ({"tiger_bracer", "bracer"}));
    set_weight(400);
    setup_wrist_eq();

    if( !clonep() ) {
        set("unit", "對");
        set("value", 5000);
        set("long",
            "一對以硬牛皮製成的護腕，上面燒印著虎紋圖案，能有效\n"
            "保護手腕在格鬥中不受傷害，是虎刀門弟子的裝備之一。\n");
        set("wear_as", "wrist_eq");
        set("apply_armor/wrist_eq", ([
            "armor": 2,
        ]));
    }
    setup();
}
