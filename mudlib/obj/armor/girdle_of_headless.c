// girdle_of_headless.c

#include <armor.h>

inherit F_WAIST_EQ;

void create()
{
    set_name("形天之怒", ({"girdle of headless", "girdle_of_headless"}));
    set_weight(1500);
    setup_waist_eq();

    if( !clonep() ) {
        set("unit", "條");
        set("value", 320000);
        set("long",
            "一條以玄鐵鍛造的腰帶，帶身刻有刑天斷首後仍持干戚起舞的圖騰，佩戴時力量倍增。\n");
        set("wear_as", "waist_eq");
        set("apply_armor/waist_eq", ([
            "armor": 30,
        ]));
    }
    setup();
}
