// yehuang_gloves.c

#include <armor.h>

inherit F_HAND_EQ;

void create()
{
    set_name("冶磺套", ({"yehuang gloves", "yehuang_gloves", "gloves"}));
    set_weight(600);
    setup_hand_eq();

    if( !clonep() ) {
        set("unit", "副");
        set("value", 100000);
        set("long",
            "一副以耐火材料打造的手套，原是冶金匠人的用具，手套表面\n"
            "粗糙堅韌，能抵禦高溫與腐蝕。\n");
        set("wear_as", "hand_eq");
        set("apply_armor/hand_eq", ([
            "armor": 10,
        ]));
    }
    setup();
}
