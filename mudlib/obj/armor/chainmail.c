// chainmail.c

#include <armor.h>

inherit F_ARMOR;

void create()
{
    set_name("連身鎖子甲", ({"chainmail", "chain mail", "armor"}));
    set_weight(12000);
    setup_armor();

    if( !clonep() ) {
        set("unit", "套");
        set("value", 200000);
        set("long",
            "一套以細密鐵環串連而成的鎖子甲，柔韌輕便，能有效抵擋刀\n"
            "劍的劈砍和箭矢的穿刺。\n");
        set("wear_as", "armor");
        set("apply_armor/armor", ([
            "armor": 25,
        ]));
    }
    setup();
}
