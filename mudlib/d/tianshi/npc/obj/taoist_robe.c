#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("道袍", ({"taoist_robe", "robe"}));
    set_weight(2500);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 4000);
        set("long",
            "一件紫色的道袍﹐袍上繡著太極八卦的圖案﹐穿上之後頗\n"
            "有幾分仙風道骨的氣質。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 3,
        ]));
    }
    setup();
}
