// aowei_belt.c

#include <armor.h>

inherit F_WAIST_EQ;

void create()
{
    set_name("獒尾帶", ({"aowei belt", "aowei_belt", "belt"}));
    set_weight(1000);
    setup_waist_eq();

    if( !clonep() ) {
        set("unit", "條");
        set("value", 200000);
        set("long",
            "一條以巨獒尾毛編織而成的腰帶，粗獷結實，佩戴時令人感到\n"
            "一股蠻荒之力湧遍全身。\n");
        set("wear_as", "waist_eq");
        set("apply_armor/waist_eq", ([
            "armor": 25,
        ]));
    }
    setup();
}
