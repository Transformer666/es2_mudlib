// jiaojao_boots.c

#include <armor.h>

inherit F_FEET_EQ;

void create()
{
    set_name("焦僥靴", ({"jiaojao boots", "jiaojao_boots"}));
    set_weight(400);
    setup_feet_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("value", 260000);
        set("long",
            "一雙精巧玲瓏的小靴，專為焦僥族的小巧身軀打造，穿上後行動如風，來去無蹤。\n");
        set("wear_as", "feet_eq");
        set("apply_armor/feet_eq", ([
            "armor": 12,
        ]));
    }
    setup();
}
