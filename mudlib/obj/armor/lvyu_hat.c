// lvyu_hat.c

#include <armor.h>

inherit F_HEAD_EQ;

void create()
{
    set_name("綠玉頂戴", ({"lvyu hat", "lvyu_hat", "hat"}));
    set_weight(500);
    setup_head_eq();

    if( !clonep() ) {
        set("unit", "頂");
        set("value", 120000);
        set("long",
            "一頂頂部鑲嵌著綠玉的官帽，玉色通透，散發著淡淡的靈氣，\n"
            "是高階文官的配飾。\n");
        set("wear_as", "head_eq");
        set("apply_armor/head_eq", ([
            "armor": 5,
        ]));
    }
    setup();
}
