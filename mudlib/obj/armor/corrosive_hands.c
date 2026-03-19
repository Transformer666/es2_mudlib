// corrosive_hands.c

#include <armor.h>

inherit F_HAND_EQ;

void create()
{
    set_name("腐蝕之手", ({"corrosive_hands", "gauntlets"}));
    set_weight(800);
    setup_hand_eq();

    if( !clonep() ) {
        set("unit", "雙");
        set("value", 250000);
        set("long",
            "一雙以不明腐蝕性材質鑄成的護手，表面不斷冒出細微的煙霧，\n"
            "能腐蝕一切有機物質，佩戴者卻絲毫不受影響。\n");
        set("wear_as", "hand_eq");
        set("apply_armor/hand_eq", ([
            "armor": 50,
        ]));
    }
    setup();
}
