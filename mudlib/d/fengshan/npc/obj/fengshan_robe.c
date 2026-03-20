// fengshan_robe.c

#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("封山道袍", ({"fengshan_robe", "robe"}));
    set_weight(1500);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 8000);
        set("long",
            "一件青灰色的道袍，衣襟上繡著封山派的山形紋章，\n"
            "布料輕薄透氣，適合練劍時穿著，是封山派弟子的常服。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 3,
        ]));
    }
    setup();
}
