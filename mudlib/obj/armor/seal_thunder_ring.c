// seal_thunder_ring.c

#include <armor.h>

inherit F_FINGER_EQ;

void create()
{
    set_name("封印雷環", ({"seal thunder ring", "seal_thunder_ring", "ring"}));
    set_weight(100);
    setup_finger_eq();

    if( !clonep() ) {
        set("unit", "枚");
        set("value", 280000);
        set("long",
            "一枚古銅色的戒指，戒面刻滿了上古祭祀符文，隱隱有雷光閃\n"
            "爍其中，據說是道家高手用以封印雷法的法器。\n");
        set("wear_as", "finger_eq");
        set("apply_armor/finger_eq", ([
            "armor": 15,
        ]));
    }
    setup();
}
