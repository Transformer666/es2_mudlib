#include <armor.h>

inherit F_FEET_EQ;

void create()
{
    set_name("夜行靴", ({"night_boots", "boots"}));
    set_weight(1500);
    setup_feet_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("value", 3000);
        set("long",
            "一雙黑色的軟底靴子﹐穿上之後行走幾乎沒有聲響﹐非常\n"
            "適合夜間行動。\n");
        set("wear_as", "feet_eq");
        set("apply_armor/feet_eq", ([
            "armor": 1,
        ]));
    }
    setup();
}
