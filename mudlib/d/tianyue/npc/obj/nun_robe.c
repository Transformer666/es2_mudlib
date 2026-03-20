// vim: syntax=lpc

#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("素色僧袍", ({"nun_robe", "robe"}));
    set_weight(1800);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 2500);
        set("long",
            "一件素色的僧袍﹐質地細緻﹐上面繡著淡雅的蓮花紋樣﹐穿\n"
            "上之後頗顯莊重。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 3,
        ]));
    }
    setup();
}
