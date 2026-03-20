// hunyuan_bag.c

#include <armor.h>

inherit F_WAIST_EQ;

void create()
{
    set_name("混元一氣袋", ({"hunyuan bag", "hunyuan_bag"}));
    set_weight(500);
    setup_waist_eq();

    if( !clonep() ) {
        set("unit", "個");
        set("value", 200000);
        set("long",
            "一個以混元真氣煉化的法袋，看似普通卻能容納萬物，佩戴腰間可護住丹田要穴。\n");
        set("wear_as", "waist_eq");
        set("apply_armor/waist_eq", ([
            "armor": 12,
        ]));
    }
    setup();
}
