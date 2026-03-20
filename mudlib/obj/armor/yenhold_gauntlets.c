// yenhold_gauntlets.c

#include <armor.h>

inherit F_HAND_EQ;

void create()
{
    set_name("厭火之拳", ({"yenhold gauntlets", "yenhold_gauntlets"}));
    set_weight(800);
    setup_hand_eq();

    if( !clonep() ) {
        set("unit", "副");
        set("value", 280000);
        set("long",
            "一副散發著灼熱氣息的拳套，以厭火族的秘法鍛造，能抵禦烈焰侵襲，出拳時帶著熊熊火焰。\n");
        set("wear_as", "hand_eq");
        set("apply_armor/hand_eq", ([
            "armor": 20,
        ]));
    }
    setup();
}
