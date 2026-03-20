// jiutian_pearl.c

#include <armor.h>

inherit F_NECK_EQ;

void create()
{
    set_name("九天鳳珠", ({"jiutian pearl", "jiutian_pearl"}));
    set_weight(200);
    setup_neck_eq();

    if( !clonep() ) {
        set("unit", "串");
        set("value", 320000);
        set("long",
            "一串由九顆鳳凰淚珠串成的項鍊，每顆珠子都散發著溫暖的金光，據說是鳳凰涅槃時留下的至寶。\n");
        set("wear_as", "neck_eq");
        set("apply_armor/neck_eq", ([
            "armor": 20,
        ]));
    }
    setup();
}
