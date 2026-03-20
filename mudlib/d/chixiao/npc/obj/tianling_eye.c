// tianling_eye.c

#include <armor.h>

inherit F_NECK_EQ;

void create()
{
    set_name("天靈眼", ({"tianling_eye", "tianling eye", "eye"}));
    set_weight(500);
    setup_neck_eq();

    if( !clonep() ) {
        set("unit", "顆");
        set("value", 500000);
        set("long",
            "一顆晶瑩剔透的寶珠，內部似乎有一隻眼睛不斷轉動，散發\n"
            "著神秘的光芒，乃是天靈的核心，佩戴後能感知周遭的靈氣。\n");
        set("wear_as", "neck_eq");
        set("apply_armor/neck_eq", ([
            "armor": 5,
        ]));
    }
    setup();
}
