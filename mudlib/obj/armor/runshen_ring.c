// runshen_ring.c

#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("潤神幻戒", ({"runshen ring", "runshen_ring", "ring"}));
    set_weight(50);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 350000);
        set("long",
            "一枚晶瑩剔透的幻戒，戒面鑲嵌著一顆七彩寶石，能抵禦風火\n"
            "雷冰四種元素的侵襲，乃是修真者夢寐以求的護身至寶。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "armor": 20,
        ]));
    }
    setup();
}
