// xincan_claw.c

#include <armor.h>

inherit F_HAND_EQ;

void create()
{
    set_name("心殘爪", ({"xincan claw", "xincan_claw", "gloves"}));
    set_weight(700);
    setup_hand_eq();

    if( !clonep() ) {
        set("unit", "副");
        set("value", 260000);
        set("long",
            "一副以猛獸利爪打造的爪套，指尖鋒利如刃，散發著嗜血的氣息，\n"
            "戴上後出手凌厲無比。\n");
        set("wear_as", "hand_eq");
        set("apply_armor/hand_eq", ([
            "armor": 10,
        ]));
    }
    setup();
}
