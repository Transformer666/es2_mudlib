// royal_sword.c

#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("英雄王者劍", ({"royal sword of honor", "royal_sword", "sword"}));
    set_weight(10000);
    setup_sword(9, 30, 200, 5);

    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "把");
        set("value", 600000);
        set("long",
            "一把氣勢磅礴的王者之劍，劍身寬厚，刻有「英雄」二字，乃\n"
            "軍備商中最頂級的武器，需雙手持握方能發揮全部威力。\n");
    }
    setup();
}
