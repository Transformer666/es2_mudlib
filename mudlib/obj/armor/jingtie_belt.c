// jingtie_belt.c

#include <armor.h>

inherit F_WAIST_EQ;

void create()
{
    set_name("精鐵環扣", ({"jingtie belt", "jingtie_belt", "belt"}));
    set_weight(1000);
    setup_waist_eq();

    if( !clonep() ) {
        set("unit", "條");
        set("value", 80000);
        set("long",
            "一條以精鐵環扣串連的腰帶，每個環扣都打磨得光滑堅固，是\n"
            "軍中常見的配備。\n");
        set("wear_as", "waist_eq");
        set("apply_armor/waist_eq", ([
            "armor": 8,
        ]));
    }
    setup();
}
