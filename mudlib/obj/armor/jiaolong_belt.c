// jiaolong_belt.c

#include <armor.h>

inherit F_WAIST_EQ;

void create()
{
    set_name("蛟龍帶", ({"jiaolong belt", "jiaolong_belt", "belt"}));
    set_weight(1200);
    setup_waist_eq();

    if( !clonep() ) {
        set("unit", "條");
        set("value", 200000);
        set("long",
            "一條以蛟龍筋為芯、蛟皮為面的腰帶，帶扣鑄成龍首形狀，\n"
            "既結實又美觀，乃是將軍級別的配飾。\n");
        set("wear_as", "waist_eq");
        set("apply_armor/waist_eq", ([
            "armor": 15,
        ]));
    }
    setup();
}
