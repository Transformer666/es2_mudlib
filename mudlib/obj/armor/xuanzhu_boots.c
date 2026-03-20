// xuanzhu_boots.c

#include <armor.h>

inherit F_FEET_EQ;

void create()
{
    set_name("玄蛛皂白靴", ({"xuanzhu boots", "xuanzhu_boots", "boots"}));
    set_weight(800);
    setup_feet_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("value", 180000);
        set("long",
            "一雙以玄蛛絲編織的輕靴，一黑一白，輕若無物，穿著者腳步\n"
            "無聲，行動敏捷。\n");
        set("wear_as", "feet_eq");
        set("apply_armor/feet_eq", ([
            "armor": 15,
        ]));
    }
    setup();
}
