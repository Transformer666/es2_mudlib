// jinggang_wrist.c

#include <armor.h>

inherit F_WRIST_EQ;

void create()
{
    set_name("精鋼護腕", ({"jinggang wrist", "jinggang_wrist", "wrist"}));
    set_weight(1500);
    setup_wrist_eq();

    if( !clonep() ) {
        set("unit", "副");
        set("value", 120000);
        set("long",
            "一副以精鋼鍛造的護腕，表面打磨得光亮如鏡，能有效抵擋刀\n"
            "劍的劈砍。\n");
        set("wear_as", "wrist_eq");
        set("apply_armor/wrist_eq", ([
            "armor": 12,
        ]));
    }
    setup();
}
