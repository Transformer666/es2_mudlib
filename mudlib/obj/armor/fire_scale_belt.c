// fire_scale_belt.c

#include <armor.h>

inherit F_WAIST_EQ;

void create()
{
    set_name("火鱗腰帶", ({"fire scale belt", "fire_scale_belt", "belt"}));
    set_weight(1500);
    setup_waist_eq();

    if( !clonep() ) {
        set("unit", "條");
        set("value", 220000);
        set("long",
            "一條以火鱗鑄造的腰帶，帶扣處鑲有一顆火紅的寶石，繫上後\n"
            "腰間微微發燙，隱約感受到火鱗的力量。\n");
        set("wear_as", "waist_eq");
        set("apply_armor/waist_eq", ([
            "armor": 12,
        ]));
    }
    setup();
}
